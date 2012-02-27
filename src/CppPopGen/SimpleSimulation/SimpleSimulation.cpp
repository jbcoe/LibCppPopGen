#include "../CppPopGenBase.h"
#include "../Random/WeightBasedSampler.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
#include <memory>

class Mutation
{
	private:
		double m_selectiveAdvantage;
		int m_count;
		int m_arrivalTime;
		int m_fixationTime;
		std::string m_name;

	public:

		Mutation(const std::string& name, int arrivalTime, double selectiveAdvantage):
			m_selectiveAdvantage(selectiveAdvantage),
			m_count(0),
			m_arrivalTime(arrivalTime), 
			m_fixationTime(-1),
			m_name(name)
	{
	}

		const std::string& name() const
		{
			return m_name;
		}

		double selectiveAdvantage() const
		{
			return m_selectiveAdvantage;
		}

		int arrivalTime() const
		{
			return m_arrivalTime;
		}

		int fixationTime() const
		{
			return m_fixationTime;
		}

		bool isFixed() const
		{                       
			return (m_fixationTime != -1);
		}

		void setFixed(int fixationTime)
		{
			m_fixationTime = fixationTime;
		}

		int count() const
		{
			return m_count;
		}

		int incrementCount()
		{
			++m_count;
		}

		int decrementCount()
		{
			--m_count;
		}

		~Mutation() {}
};

class MultiplicativeFitnessModel
{
	public:

		static double GetFitness(const std::vector<Mutation*>& organism )
		{
			double fitness = 1.0;
			for ( const Mutation* pMutation : organism )
			{
				fitness *= ( 1.0 + pMutation->selectiveAdvantage() );
			}
			return fitness;
		}

};

template <class Mutation_t>
class AsexualReproductionModel
{ 
	public:
		typedef std::vector<Mutation_t*> Organism;

		template <class Sampler_t, class Engine_t>
			static std::vector<Mutation_t*> GetNewborn(Sampler_t& sampler, Engine_t& engine)
			{
				Organism* pOrganism = sampler.GetValue(engine);
				return std::move(Organism(*pOrganism));
			}
};

class NullMutationModel
{
	public:
		template <class Mutation_t>
			static void Mutate (std::vector<Mutation_t*>& organism)
			{
			}
};

class LostOrFixedMutationsToCOUT
{
	public:
		template <class Mutation_t>
			static void ReportFixedMutation(const Mutation_t* mutation, int timestep)
			{
				std::cout << mutation->name() << " was fixed at step " << timestep << std::endl; 
			}

		template <class Mutation_t>
			static void ReportLostMutation(const Mutation_t* mutation, int timestep)
			{
				std::cout << mutation->name() << " was lost at step " << timestep << std::endl; 
			}
};

template <class FitnessModel_t, class ReproductionModel_t, class MutationModel_t, class Reporter_t>
class Population
{
	public:

		Population(size_t popSize) : m_timestep(0), m_popSize(popSize) 
	{
		m_organisms.resize(popSize);
		m_newOrganisms.resize(popSize);
		m_engine.seed(101L);
		for ( int i=0; i<m_popSize; ++i )
		{
			std::stringstream ss;
			ss << "Mutation_" << i;
			m_mutations.push_back(std::unique_ptr<Mutation>(new Mutation(ss.str(), 0, 0.0)));
			Mutation* pMutation = m_mutations.back().get();
			pMutation->incrementCount();
			m_organisms[i].push_back(pMutation);
		}
	}

		typedef std::vector<Mutation*> Organism;

		void next()
		{
			++m_timestep;

			m_newOrganisms.clear();

			/// Set up sampler
			m_organismSampler.clear();
			for ( Organism& organism : m_organisms )
			{
				m_organismSampler.add(FitnessModel_t::GetFitness(organism),&organism); 
			}


			/// Sample and mutate
			for ( int i=0; i<m_popSize; ++i )
			{
				m_newOrganisms.push_back(ReproductionModel_t::GetNewborn(m_organismSampler, m_engine));
				MutationModel_t::Mutate(m_newOrganisms.back());
			}

			//decrement counts for mutations in current gen
			for ( Organism& organism : m_organisms )
			{
				for ( Mutation* pMutation: organism )
				{
					pMutation->decrementCount();
				}
			}

			//increase counts for mutations in next gen
			for ( Organism& organism : m_newOrganisms )
			{                                
				for ( Mutation* pMutation: organism )
				{
					pMutation->incrementCount();
				}
			}

			for ( const auto& pMutation : m_mutations )
			{
				if ( pMutation->isFixed() ) continue;

				if ( pMutation->count() == 0 )
				{
					pMutation->setFixed(m_timestep);  
					Reporter_t::ReportLostMutation(pMutation.get(), m_timestep);
				}
				else if ( pMutation->count() == m_popSize )
				{
					pMutation->setFixed(m_timestep);
					Reporter_t::ReportFixedMutation(pMutation.get(), m_timestep);
				}
			}

			// fill organisms in m_organisms with mutations 
			// from m_newOrganisms unless the mutations have fixed
			m_organisms.clear();
			for ( Organism& newOrganism : m_newOrganisms )
			{
				Organism nextGenOrganism;
				for ( Mutation* pMutation: newOrganism )
				{
					if ( ! pMutation->isFixed() )
					{
						nextGenOrganism.push_back(pMutation);
					}
				}
				m_organisms.push_back(std::move(nextGenOrganism));
			}

			m_newOrganisms.clear();


			//Clear up dead mutations
			m_mutations.erase( 
					std::remove_if(m_mutations.begin(), m_mutations.end(),
						[](std::unique_ptr<Mutation>& m)
						{
						return m->isFixed();
						}) 
					, m_mutations.end());

		}

		bool hasSegregatingMutations()
		{
			return ! m_mutations.empty();
		}

	private:
		size_t m_timestep;
		size_t m_popSize;
		std::mt19937 m_engine;
		PopGen::WeightBasedSampler<Organism*> m_organismSampler;
		std::vector<std::unique_ptr<Mutation>> m_mutations;
		std::vector<std::vector<Mutation*>> m_organisms;
		std::vector<std::vector<Mutation*>> m_newOrganisms;
};

int main(int argc, char** argv)
{
	Population<MultiplicativeFitnessModel, AsexualReproductionModel<Mutation>, NullMutationModel, LostOrFixedMutationsToCOUT> population(100);
	while ( population.hasSegregatingMutations() )
	{
		population.next();
	}
}

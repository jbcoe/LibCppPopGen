#include <CppPopGenBase.h>
#include <Random/WeightBasedSampler.hpp>
#include <SimpleSimulation/Mutation.h>
#include <SimpleSimulation/MutationPool.h>
#include <SimpleSimulation/MultiplicativeFitnessModel.h>
#include <SimpleSimulation/AsexualReproductionModel.h>
#include <SimpleSimulation/NullMutationModel.h>
#include <SimpleSimulation/LostOrFixedMutationsToCOUT.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
#include <memory>

template <class FitnessModel_t, class ReproductionModel_t, class MutationModel_t, class Reporter_t>
class Population
{
	public:

		Population(size_t popSize) : m_timestep(0), m_popSize(popSize), 
		m_lostMutationFunctor(m_timestep), m_fixedMutationFunctor(m_timestep) 
	{
		m_organisms.resize(popSize);
		m_newOrganisms.resize(popSize);
		m_engine.seed(101L);
		for ( int i=0; i<m_popSize; ++i )
		{
			std::stringstream ss;
			ss << "Mutation_" << i;
			Mutation* pMutation = m_mutationPool.addMutation(ss.str(), 0, 0.0);
			pMutation->incrementCount();
			m_organisms[i].push_back(pMutation);
		}
	}

		typedef std::vector<Mutation*> Organism;

		void next()
		{
			++m_timestep;

			makeNewborn();

			newbornBecomeAdults();

			//Clear lost and fixed mutations
			m_mutationPool.clearMutationsWithCount(0,m_lostMutationFunctor);
			m_mutationPool.clearMutationsWithCount(m_popSize,m_fixedMutationFunctor);
		}

		bool hasSegregatingMutations()
		{
			return ! m_mutationPool.empty();
		}

	private:

		class FixedMutationFunctor
		{
			public:
				FixedMutationFunctor(const size_t& timestep) : m_timestepRef(timestep) {}

				void operator()(const Mutation* mutation)
				{
					Reporter_t::ReportFixedMutation(mutation,m_timestepRef);
				}

			private:
				const size_t& m_timestepRef;
		};

		class LostMutationFunctor
		{
			public:
				LostMutationFunctor(const size_t& timestep) : m_timestepRef(timestep) {}

				void operator()(const Mutation* mutation)
				{
					Reporter_t::ReportLostMutation(mutation,m_timestepRef);
				}

			private:
				const size_t& m_timestepRef;
		};


		void makeNewborn()
		{
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
				m_newOrganisms.push_back(
						ReproductionModel_t::GetNewborn(m_organismSampler, m_engine));
				MutationModel_t::Mutate(m_newOrganisms.back());
			}
		}

		void newbornBecomeAdults()
		{
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

			// fill organisms in m_organisms with mutations 
			// from m_newOrganisms unless the mutations have fixed
			m_organisms.clear();
			for ( Organism& newOrganism : m_newOrganisms )
			{
				Organism nextGenOrganism;
				for ( Mutation* pMutation: newOrganism )
				{
					if ( pMutation->count() != 0 && pMutation->count() != m_popSize )
					{
						nextGenOrganism.push_back(pMutation);
					}
				}
				m_organisms.push_back(std::move(nextGenOrganism));
			}

			m_newOrganisms.clear();
		}

		static bool MutationIsFixed(std::unique_ptr<Mutation>& m)
		{
			return m->isFixed();
		}

		size_t m_timestep;
		size_t m_popSize;
		LostMutationFunctor m_lostMutationFunctor;
		FixedMutationFunctor m_fixedMutationFunctor;
		std::mt19937 m_engine;
		PopGen::WeightBasedSampler<Organism*> m_organismSampler;
		MutationPool<Mutation> m_mutationPool;
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

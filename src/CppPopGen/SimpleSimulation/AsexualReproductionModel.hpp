#pragma once
#include <vector>

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


#include <iostream>

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


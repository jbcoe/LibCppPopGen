#include <vector>

class NullMutationModel
{
	public:
		template <class Mutation_t>
			static void Mutate (std::vector<Mutation_t*>& organism)
			{
			}
};


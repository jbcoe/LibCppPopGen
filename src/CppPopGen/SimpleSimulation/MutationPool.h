#include <memory>
#include <vector>

template <class Mutation_t>
class MutationPool
{
	public:

		template <typename... ConstructorArgs>
			Mutation_t* addMutation(ConstructorArgs... args)
			{
				m_mutations.push_back(std::unique_ptr<Mutation_t>(new Mutation_t(args...)));
				return m_mutations.back().get();
			}

		bool empty() const { return m_mutations.empty(); }

		template <class MutationFunctor_t>
			void clearMutationsWithCount(size_t count, MutationFunctor_t& mutationFunctor)
			{
				m_mutations.erase( std::remove_if(m_mutations.begin(), m_mutations.end(),
							[&](std::unique_ptr<Mutation_t>& m)->bool
							{
							if ( m->count() == count )
							{
							mutationFunctor(m.get());
							return true;
							}
							return false;
							}), m_mutations.end());
			}

	private:

		std::vector<std::unique_ptr<Mutation_t>> m_mutations;
};


#include <vector>

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


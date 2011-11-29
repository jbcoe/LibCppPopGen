#include <iostream>
#include <vector>
#include <random>

template <typename Value_t>
class WeightBasedSampler
{
	public:

		WeightBasedSampler() : m_weightSum(0.0) 
	{
	}

		void Add(double weight, Value_t value)
		{       
			m_weightSum += weight;
			m_cumulativeWeights.push_back(m_weightSum);
			m_values.push_back(value);
			m_uniformDist = std::uniform_real_distribution<double>(0,m_cumulativeWeights.back());
		}

		template <typename RandomEngine_t>
			Value_t GetValue(RandomEngine_t& randomEngine)
			{
				double randomValue = m_uniformDist(randomEngine);
				return m_values[getIndex(randomValue)];
			}

		int getIndex(double value) 
		{
			if ( m_cumulativeWeights.empty() || value > m_cumulativeWeights.back() )
			{
				return -1;
			}

			int left, right, middle;
			int index = -1;

			left = 0;
			right = m_cumulativeWeights.size() - 1;

			while (left <= right) 
			{
				middle = (left + right + 1) / 2;

				if (middle == 0) 
				{
					if ( value < m_cumulativeWeights[0] ) 
					{
						index = 0;
					}
					break;
				}
				else if ( value <= m_cumulativeWeights[middle] && value > m_cumulativeWeights[middle-1] )
				{
					index = middle;
					break;
				} 
				else if ( value > m_cumulativeWeights[middle] ) 
				{
					left = middle + 1;
				} 
				else 
				{
					right = middle - 1;
				}
			}
			return index;
		}

	private:
		std::uniform_real_distribution<double> m_uniformDist;
		std::vector<double> m_cumulativeWeights;
		std::vector<Value_t> m_values;
		double m_weightSum;
};

int main(int argc, char* argv[])
{
	std::mt19937 mt;

	WeightBasedSampler<std::string> stringSampler;
	stringSampler.Add(10.,"Cat");
	stringSampler.Add(1.,"Pig");

	for ( int i=0; i<1000; ++i )
	{
		std::cout << stringSampler.GetValue(mt) << std::endl;
	}
}


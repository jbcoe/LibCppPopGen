#include <vector>
#include <random>
#include <stdexcept>

template <typename Value_t>
class WeightBasedSampler
{
	public:

		WeightBasedSampler() 
			: m_weightSum(0.0) 
		{
		}

		void add(double weight, Value_t value)
		{ 
			if ( weight < 0.0 )
				throw std::runtime_error("Weight in weight-based sampler must not be negative");
			m_weightSum += weight;
			m_cumulativeWeights.push_back(m_weightSum);
			m_values.push_back(value);
			m_uniformDist = std::uniform_real_distribution<double>(0,m_cumulativeWeights.back());
		}

		void reserve(size_t reservedSize)
		{
			m_cumulativeWeights.reserve(reservedSize);
			m_values.reserve(reservedSize);
		}

		void clear()
		{
			m_cumulativeWeights.clear();
			m_values.clear();
			m_weightSum = 0.0;
		}


		Value_t& GetValueForWeight( double cumulativeWeightValue )
		{
			int valueIndex = getIndex(cumulativeWeightValue, m_cumulativeWeights);
			if ( valueIndex < 0 )
				throw std::runtime_error("Weight value cannot be found in cumulative weights");
			return m_values[valueIndex];
		}

		template <typename RandomEngine_t>
			Value_t& GetValue(RandomEngine_t& randomEngine)
			{
				double randomValue = m_uniformDist(randomEngine);
				int valueIndex = getIndex(randomValue, m_cumulativeWeights);
				if ( valueIndex < 0 )
					throw std::runtime_error("Weight value cannot be found in cumulative weights");
				return m_values[valueIndex];
			}

		/// return -1 if index cannot be found
		template <typename T>
			static int getIndex(T value, const std::vector<T>& weights) 
			{
				if ( weights.empty() || value > weights.back() )
				{
					return -1;
				}

				int left, right, middle;
				int index = -1;

				left = 0;
				right = weights.size() - 1;

				while (left <= right) 
				{
					middle = (left + right + 1) / 2;

					if (middle == 0) 
					{
						if ( value <= weights[0] ) 
						{
							index = 0;
						}
						break;
					}
					else if ( value <= weights[middle] && value > weights[middle-1] )
					{
						index = middle;
						break;
					} 
					else if ( value > weights[middle] ) 
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

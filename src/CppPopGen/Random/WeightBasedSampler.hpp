#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <CppPopGen/CppPopGenBase.hpp>

BEGIN_CPP_POPGEN

template <typename Value_t>
class WeightBasedSampler
{
	struct WeightsAndValue
	{
		double m_weight;
		double m_cumulativeWeight;
		Value_t m_value;

		WeightsAndValue(double weight, Value_t value) : m_weight(weight),
		m_value(value), m_cumulativeWeight(0.0) {}
	};

	typedef std::vector<WeightsAndValue> WeightsAndValues;

	public:

  class WeightBasedSamplerException : public std::runtime_error
	{
		public:
			WeightBasedSamplerException(const std::string& err) 
			: std::runtime_error(err) {}
	};

	WeightBasedSampler() 
		: m_weightSum(0.0) 
	{
	}

	void add(double weight, Value_t value)
	{ 
		if ( weight <= 0.0 )
			throw WeightBasedSamplerException("Weight in weight-based sampler must not be negative");
		m_weightSum += weight;
		m_weightsAndValues.push_back(WeightsAndValue(weight,value));
		m_weightsAndValues.back().m_cumulativeWeight = m_weightSum;
		m_uniformDist = std::uniform_real_distribution<double>(0,m_weightSum);
	}

	void reserve(size_t reservedSize)
	{
		m_weightsAndValues.reserve(reservedSize);
	}

	void clear()
	{
		m_weightsAndValues.clear();
		m_weightSum = 0.0;
	}

	Value_t& GetValueForWeight( double cumulativeWeightValue )
	{
		auto find_value = findValue(cumulativeWeightValue);
		if ( find_value == m_weightsAndValues.end() )
			throw WeightBasedSamplerException("Weight value cannot be found in cumulative weights");
		return find_value->m_value;
	}

	template <typename RandomEngine_t>
		Value_t& GetValue(RandomEngine_t& randomEngine)
		{
			double randomValue = m_uniformDist(randomEngine);
			return GetValueForWeight(randomValue);
		}

	typename WeightsAndValues::iterator findValue( double value )
	{
		auto lowerBound_it = std::lower_bound(m_weightsAndValues.begin(),
				m_weightsAndValues.end(), value, 
				[](const WeightsAndValue& w, double r)
				{
					return w.m_cumulativeWeight < r;	
				});
		
		return lowerBound_it;
	}

	private:
	std::uniform_real_distribution<double> m_uniformDist;

	double m_weightSum;

	WeightsAndValues m_weightsAndValues;
};

END_CPP_POPGEN

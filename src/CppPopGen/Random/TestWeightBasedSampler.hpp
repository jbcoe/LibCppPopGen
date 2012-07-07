#include <CppPopGen/Random/WeightBasedSampler.hpp>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

class TestWeightBasedSampler : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TestWeightBasedSampler );
	CPPUNIT_TEST ( testCumulativeWeightLookup ); 
	CPPUNIT_TEST_SUITE_END();

	protected:
	void testCumulativeWeightLookup()
	{
		PopGen::WeightBasedSampler<std::string> stringSampler;
		stringSampler.add(2.,"Cat");

		CPPUNIT_ASSERT(stringSampler.GetValueForWeight(0.) == "Cat");
		CPPUNIT_ASSERT(stringSampler.GetValueForWeight(1.) == "Cat");
		CPPUNIT_ASSERT(stringSampler.GetValueForWeight(2.) == "Cat");

		stringSampler.add(1.,"Pig");

		CPPUNIT_ASSERT(stringSampler.GetValueForWeight(0.) == "Cat");
		CPPUNIT_ASSERT(stringSampler.GetValueForWeight(1.) == "Cat");
		CPPUNIT_ASSERT(stringSampler.GetValueForWeight(2.) == "Cat");
		CPPUNIT_ASSERT(stringSampler.GetValueForWeight(2.01) == "Pig");
		CPPUNIT_ASSERT(stringSampler.GetValueForWeight(3.) == "Pig");
	}
};

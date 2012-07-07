#include <cppunit/TestResult.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <CppPopGen/Random/TestWeightBasedSampler.hpp>

int main (int argc, char** argv)
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( TestWeightBasedSampler::suite() );
	runner.run();
	return 0;
}

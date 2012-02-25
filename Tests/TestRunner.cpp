#include <cppunit/TestResult.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

class ExampleTestCase : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( ExampleTestCase );
  CPPUNIT_TEST ( testAddition ); 
	CPPUNIT_TEST_SUITE_END();

protected:
	void testAddition()
	{
		CPPUNIT_ASSERT( 2+2 == 4 );
	}
};


int main (int argc, char** argv)
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( ExampleTestCase::suite() );
	runner.run();
	return 0;
}

#include <iostream>
#include <vector>
#include <random>
#include "WeightBasedSampler.hpp"

int main(int argc, char* argv[])
{
	std::mt19937 mt;

	WeightBasedSampler<std::string> stringSampler;
	stringSampler.add(8.,"Cat");
	stringSampler.add(2.,"Pig");

	for ( int i=0; i<10; ++i )
	{
		std::cout << stringSampler.GetValue(mt) << std::endl;
	}
}


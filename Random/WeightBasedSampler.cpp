#include <iostream>
#include <vector>
#include <random>
#include "WeightBasedSampler.hpp"

int main(int argc, char* argv[])
{
	std::mt19937 mt;

	WeightBasedSampler<std::string> stringSampler;
	stringSampler.Add(10.,"Cat");
	stringSampler.Add(1.,"Pig");

	for ( int i=0; i<100; ++i )
	{
		std::cout << stringSampler.GetValue(mt) << std::endl;
	}
}


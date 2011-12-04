#include <iostream>
#include <vector>
#include <random>
#include "WeightBasedSampler.hpp"

int main(int argc, char* argv[])
{
	int count = 10;
  if ( argc > 1 )
	{
  	count = atoi(argv[1]);
	}

	std::mt19937 mt;

	WeightBasedSampler<std::string> stringSampler;
	stringSampler.add(100.,"Cat");
	stringSampler.add(1.,"Pig");

	for ( int i=0; i<count; ++i )
	{
		std::cout << stringSampler.GetValue(mt) << std::endl;
	}
}


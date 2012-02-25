#include <iostream>
#include <assert.h>
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
	stringSampler.add(2.,"Cat");

	assert(stringSampler.GetValueForWeight(0.) == "Cat");
	assert(stringSampler.GetValueForWeight(1.) == "Cat");
	assert(stringSampler.GetValueForWeight(2.) == "Cat");

	stringSampler.add(1.,"Pig");

	assert(stringSampler.GetValueForWeight(0.) == "Cat");
	assert(stringSampler.GetValueForWeight(1.) == "Cat");
	assert(stringSampler.GetValueForWeight(2.) == "Cat");
	assert(stringSampler.GetValueForWeight(2.01) == "Pig");
	assert(stringSampler.GetValueForWeight(3.) == "Pig");

	std::cout << "Test succeeded" << std::endl;
}


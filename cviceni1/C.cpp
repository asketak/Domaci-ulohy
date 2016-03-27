#include <map>
#include <array>
#include <cmath>
#include "gnuplot-iostream/gnuplot-iostream.h"
#include <typeinfo>
#include <cairo/cairo.h>
#include <cassert>

const int SPIRAL_IMAGE_EDGE_SIZE = 3;
const int MAX_PRIME = SPIRAL_IMAGE_EDGE_SIZE * SPIRAL_IMAGE_EDGE_SIZE+1;
const int CENTER_COORDINATE = (SPIRAL_IMAGE_EDGE_SIZE - 1) /2 ;

bool isPrime(int x){
	if (x == 1)
	{
		return false;
	}
	if (x == 2)
	{
		return true;
	}
	for (int i = 2; i < x; ++i)
	{
		if (x % i == 0)
		{
			return false;
		}
	}
	return true;
}

void write_spiral(std::array<bool, MAX_PRIME> points)
{
	for (int i = 1; i < MAX_PRIME; ++i)
	{
		std::cout << "IT" << std::endl;
		if (points[i])
		{
			std::cout << "PRVOCISLO" << std::endl;
		}
		
	}

}

std::array<bool, MAX_PRIME> fillPrimes(){
	std::array<bool, MAX_PRIME> primes;
	for (int i = 1; i < MAX_PRIME; ++i)
	{
		primes[i] = isPrime(i);
	}
	return primes;
}

int main(int argc, char const *argv[])
{
	assert(SPIRAL_IMAGE_EDGE_SIZE%2==1);
	std::array<bool, MAX_PRIME> primes = fillPrimes();
	//write_spiral(primes);

	return 0;
}
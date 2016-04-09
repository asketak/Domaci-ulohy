#include <iostream>
#include <cmath>

double power(double x, int n){
	return n == 1 ?  x :  x*power(x,n-1);
}

/**
float taylor_power(float base, float exponent){
	int down_exponent = down_exponent - (down_exponent % 1);
	int up_exponent = down_exponent + 1;
	float old_taylor = 0;
	float new_taylor = 1000;

	for(int steps = 0; new_taylor - old_taylor > 1 || new_taylor - old_taylor < -1 || steps == 0) {
		up_taylor = 
		diff = up_taylor - down_taylor > 0 ? up_taylor - down_taylor : down_taylor - up_taylor;



	}
}
**/

float sqrt(int n, int d){
	double max = n;
	double min = 0;
	double mid = min + (max-min)/2;
	double resolution = 0.02;
	while ( max - min > resolution)
	{
		std::cout << "max:min=" << max << ":" << min << std::endl;
		mid = min + (max-min)/2;
		if (power(mid,d) > n)
		{
			max = mid; 
		}else{
			min = mid; 
		}
	}
	return mid; 
}
int main(int argc, char const *argv[])
{
	std::cout << power(10,2.5) << std::endl;
	std::cout << power(2,3.7) << std::endl;
	std::cout << power(2,4) << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << sqrt(25,2) << std::endl;
	std::cout << sqrt(20,2) << std::endl;
	std::cout << sqrt(16,2) << std::endl;
	std::cout << sqrt(256,4) << std::endl;
	std::cout << "-----------" << std::endl;


	return 0;
}
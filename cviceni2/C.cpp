#include <iostream>
#include <cmath>

float power(float x, int n){
	return n == 1 ?  x :  x*power(x,n-1);
}

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

float sqrt(int n, int d){
	float quess = 1;
	float lastQuess = 0;
	bool switched = false;
	while (!switched)
	{
		if (power(quess,d) > n)
		{
			switched = true;
		}
		lastQuess = quess;
		quess *= 2;
	}



}
int main(int argc, char const *argv[])
{
	std::cout << power(10,2.5) << std::endl;
	std::cout << power(2,3.7) << std::endl;
	std::cout << power(2,4) << std::endl;
	std::cout << "-----------" << std::endl;


	return 0;
}
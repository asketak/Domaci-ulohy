#include <iostream>
#include <cmath>
#include <random>
#include <tuple>

float liebnitz_pi(int accuracy ){
	double pi_fourth = 1;
	int op = -1;
	int divisor = 3;
	for(int i = 0; i < accuracy; ++i) {
		pi_fourth += op*1/(double)divisor;
		op *= -1;
		divisor += 2;
	}
	return pi_fourth * 4;
}

float archimedes_pi(int accuracy){
	long long polygon_sides = 6;
	float polygon_side_length = 1;
	for (int i = 0; i < accuracy; ++i)
	{
		polygon_sides *= 2;
		double perpendicular_length = std::sqrt(1 - std::pow(polygon_side_length/2,2) );
		polygon_side_length = std::sqrt( std::pow(1-perpendicular_length,2) + std::pow(polygon_side_length/2, 2));
	}
	return polygon_side_length * polygon_sides / 2;
}

float monte_carlo_pi( const int accuracy){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    std::vector<std::tuple<float,float>> points;
    float points_inside = 0;
    for (int n = 0; n < accuracy; ++n) {
        points.push_back(std::make_tuple(dis(gen) ,dis(gen)));
    }
    for (auto i = points.begin(); i != points.end(); ++i)
    {
    	if (std::pow(std::get<0>(*i),2) + (std::pow(std::get<1>(*i),2) ) < 1) 
    	{
    		points_inside++;
    	}
    	
    }
    return points_inside / accuracy * 4 ;
}

int main(int argc, char const *argv[])
{
	std::cout << liebnitz_pi(10) << std::endl;
	std::cout << liebnitz_pi(30) << std::endl;
	std::cout << liebnitz_pi(100) << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << archimedes_pi(3) << std::endl;
	std::cout << archimedes_pi(5) << std::endl;
	std::cout << archimedes_pi(15) << std::endl;

	std::cout << "------------------" << std::endl;
	std::cout << monte_carlo_pi(500) << std::endl;
	std::cout << monte_carlo_pi(5000) << std::endl;
	std::cout << monte_carlo_pi(50000) << std::endl;
	std::cout << monte_carlo_pi(500000) << std::endl;

	return 0;
}
#include <iostream>
#include <map>
#include <cmath>
#include <random>
#include <vector>
#include <string>
#include <cairo/cairo.h>
#include "turtle.h"


const int STEP_SIZE = 3;
const int ANGLE = 60;

const int PIXEL_SIZE = 2;

const int NUMBER_OF_ITERATIONS = 5;

const double IMAGE_SIZE = 1000;

using Point =std::pair<double,double>  ;

std::string expand_string( std::string root, std::map<char, std::string> rules, int iterations ){ 

	std::string ret = "";

	if (iterations == 0)
	{
		return root;
	}
	for (auto i = root.begin(); i != root.end(); ++i)
	{
		auto it = rules.find(*i);

		if ( it == rules.end())
		{
			ret.push_back(*i);
		}else{
			ret.append(it->second);
		}
	}
	ret = expand_string(ret,rules,iterations-1);

	return ret;
}



void run_plan(std::string plan ) {
	Turtle turtle(IMAGE_SIZE/2,IMAGE_SIZE/2,IMAGE_SIZE);


	turtle.pendown();
	for (auto i = plan.begin(); i != plan.end(); ++i)
	{
		if (*i == 'F')
		{
			turtle.forward(STEP_SIZE);
		}
		if (*i == 'B')
		{
			turtle.back(STEP_SIZE);
		}
		if (*i == '-')
		{
			turtle.left(ANGLE);
		}
		if (*i == '+')
		{
			turtle.right(ANGLE);
		}
	}


	turtle.save("B.png");

}


int main(int argc, char const *argv[])
{

	std::map<char,std::string> rules;	
	rules['F'] = "F+F--F+F";
	std::string root = "F--F--F";

	std::string plan = expand_string(root, rules, NUMBER_OF_ITERATIONS);
	//std::cout << plan << std::endl;
	run_plan(plan);

	return 0;
}

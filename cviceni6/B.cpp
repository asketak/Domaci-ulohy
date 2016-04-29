#include <iostream>
#include <map>
#include <cmath>
#include <random>
#include <vector>
#include <string>
#include <cairo/cairo.h>


const int PIXEL_SIZE = 2;
const int NUMBER_OF_LINES = 3;
const double RADIUS = 200;
const double FRACTION = 1 / 2.0;

const int NUMBER_OF_ITERATIONS = 10000;

const double IMAGE_SIZE = RADIUS*2*PIXEL_SIZE;
const double IMAGE_PIXEL_SIZE = IMAGE_SIZE*1.1;
const double MIDDLE = IMAGE_SIZE/2;

using Point =std::pair<double,double>  ;
using Rule = std::pair<char,std::string>  ;


std::string expand_rules( char root, std::map<char, std::string> rules, int iterations ){ 

	std::string ret = "";
	auto it = rules.find(root);

	if (iterations == 0 || it == rules.end())
	{
		return ret;
	}

		for (auto i = prev_plan.begin(); i != prev_plan.end(); ++i)
		{
			ret.append(expand_rules(*i,rules,iterations-1));
		}

	return ret;
}



void run_plan(std::string plan ) {
}


int main(int argc, char const *argv[])
{

	std::vector<Rule> rules;	
	rules.push_back(std::make_pair('B',"B-A-B"));
	rules.push_back(std::make_pair('A',"A+B+A"));
	char root = 'B';

	std::string plan = expand_rules(root, rules, NUMBER_OF_ITERATIONS);
	std::cout << plan << std::endl;
//	run_plan(cr,plan);

	return 0;
}

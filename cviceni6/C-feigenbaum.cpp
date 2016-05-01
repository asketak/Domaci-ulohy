#include <iostream>
#include <map>
#include <cmath>
#include <random>
#include <vector>
#include <string>
#include <cairo/cairo.h>
#include "turtle.h"

#include "gnuplot-iostream/gnuplot-iostream.h"


const int MIN_X = 0;
const int MAX_X = 4;
const int MIN_Y = 0;
const int MAX_Y = 1;

const int PIXEL_SIZE = 1;

const int NUMBER_OF_ITERATIONS = 5000;
const int NUMBER_OF_ITERATIONS_TO_PLOT = 100;

using Point =std::pair<double,double>  ;

std::vector<Point> generate_data()  {
	const double STEP_SIZE = (MAX_X-MIN_X) / 100.0;
	std::cout << STEP_SIZE << std::endl;
	std::vector<Point> ret;
	for (double r = 0; r < MAX_X; r += STEP_SIZE)
	{
		double y = 0.5;
		for (int i = 0; i < NUMBER_OF_ITERATIONS; ++i)
		{
			y = r * y*(1-y);
			if (i > NUMBER_OF_ITERATIONS - NUMBER_OF_ITERATIONS_TO_PLOT)
			{
				double rounded_y = (y * 100) / 100.0;
				ret.push_back(std::make_pair(r,rounded_y));
			}
		}	


	}
	return ret;
}


void plot_data(std::vector<Point> data, std::string filename) {
	Gnuplot gp;
	gp << "set terminal png "<< "\n"<< " set output \""<< filename <<"\"" << "\n";
	gp << "set xrange [" << MIN_X << ":" << MAX_X << "]\nset yrange [ "<< MIN_Y << ":" << MAX_Y <<"]\n";
	gp << "plot '-' with points title 'cubic'\n";
	gp.send1d(data);

}


int main(int argc, char const *argv[])
{

	std::vector<Point> data =  generate_data();
	plot_data(data, "C.png");

	return 0;
}

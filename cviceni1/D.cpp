#include <map>
#include <iostream>
#include <array>
#include <cmath>
#include "gnuplot-iostream/gnuplot-iostream.h"
#include <typeinfo>
#include <cairo/cairo.h>
#include <cassert>

const int PIXEL_SIZE = 10; // one number/point in ulman spiral correspon to PIXEL_SIZE * PIXEL_SIZE rectangle in image
const int IMAGE_SIZE = 50; // How many rectangles wide the image will be
const int IMAGE_PIXEL_SIZE = IMAGE_SIZE*PIXEL_SIZE; // Acutal pixel wise size of image


int gcd(int a, int b) {
	return b == 0 ? a: gcd(b, a % b);
}

int gcd_modulo_steps(int a, int b) {
	return (b == 0 || a == 0) ? 1:  a>b? gcd_modulo_steps(b, a % b)+1 : gcd_modulo_steps(b%a, a)+1;
}

int gcd_minus_steps(int a, int b) {
	return (b == 0 || a == 0) ? 1 :  a>b? gcd_minus_steps(b, a - b)+1 : gcd_minus_steps(b-a, a)+1;
}

auto tuple_compare(const std::tuple<int, int, int>& left, const std::tuple<int, int, int>& right){
	return (std::get<2>(left) <  std::get<2>(right));
}

// ZDE ZACINA ZKOPIROVANY KOD
std::tuple<double,double,double> hsvToRgb( double h, double s, double v){
    double r, g, b;

    int i = std::floor(h * 6);
    double f = h * 6 - i;
    double p = v * (1 - s);
    double q = v * (1 - f * s);
    double t = v * (1 - (1 - f) * s);

    switch(i % 6){
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

    return std::make_tuple(r , g , b );
}
// ZDE KONCI ZKOPIROVANY KOD

void plot_tuples_with_color(std::vector<std::tuple<int,int,int>> data, std::string filename)
{

	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,IMAGE_PIXEL_SIZE, IMAGE_PIXEL_SIZE);
	cairo_t *cr = cairo_create (surface); 

	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);
	auto max_tuple = (*std::max_element(data.begin(), data.end(),tuple_compare));
	int max_color = std::get<2>(max_tuple);
	//std::cout << "MAX COLOR:" << a << ":" << b <<":" << max_color << std::endl;

	for (int x = 0; x < data.size(); ++x){
		{
			cairo_rectangle (cr, std::get<0>(data[x])*PIXEL_SIZE, IMAGE_PIXEL_SIZE - PIXEL_SIZE - std::get<1>(data[x])*PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE);
			double color = (double)std::get<2>(data[x]) / max_color;
			//std::cout << "color:" << color << std::endl;
			std::tuple<double,double,double> rgb = hsvToRgb( color, 1, 1);
			cairo_set_source_rgb (cr, std::get<0>(rgb), std::get<1>(rgb),std::get<2>(rgb));
			cairo_fill (cr);
		}

		//cairo_destroy (cr);
		cairo_surface_write_to_png (surface, filename.c_str());
		//cairo_surface_destroy (surface);
	}}


	int main(int argc, char const *argv[])
	{

		std::vector<std::tuple<int,int,int>> data ;
		for (int x = 0; x < IMAGE_SIZE; ++x)
		{
			for (int y = 0; y < IMAGE_SIZE; ++y)
			{
				auto tuple = std::make_tuple(x,y,gcd(x,y));
				data.push_back(tuple);
				//std::cout << "DATA1: x = " << std::get<0>(tuple)  << " y =" << std::get<1>(tuple) << " val " << std::get<2>(tuple) << std::endl;
			}
		}

		std::vector<std::tuple<int,int,int>> data2 ;
		for (int x = 0; x < IMAGE_SIZE; ++x)
		{
			for (int y = 0; y < IMAGE_SIZE; ++y)
			{
				auto tuple = std::make_tuple(x,y,gcd_modulo_steps(x,y));
				data2.push_back(tuple);
				std::cout << "DATA2:" << std::get<2>(data2[x*IMAGE_SIZE + y]) << std::endl;
			}
		}

		std::vector<std::tuple<int,int,int>> data3 ;
		for (int x = 0; x < IMAGE_SIZE; ++x)
		{
			for (int y = 0; y < IMAGE_SIZE; ++y)
			{
				auto tuple = std::make_tuple(x,y,gcd_minus_steps(x,y));
				data3.push_back(tuple);
				std::cout << "DATA3:" << std::get<2>(data3[x*IMAGE_SIZE + y]) << std::endl;
			}
		}

		plot_tuples_with_color(data,"gcd.png");
		plot_tuples_with_color(data2,"gcd-modulo-steps.png");
		plot_tuples_with_color(data3,"gcd-minust-steps.png");

		return 0;
	}

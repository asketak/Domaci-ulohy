#include <iostream>
#include <map>
#include <cmath>
#include <random>
#include <vector>
#include <string>
#include <complex>
#include <cairo/cairo.h>

double SIZE = 1;
double STEP_SIZE = 0.005;
double PIXEL_SIZE  = 1;
double IMAGE_PIXEL_SIZE  = SIZE/STEP_SIZE * 2 * PIXEL_SIZE;
std::complex<double> red(1,0);
std::complex<double> green(-0.5,std::sqrt(3)/2);
std::complex<double> blue(-0.5, -std::sqrt(3)/2);
const int iterations = 100;

void put_pixel(cairo_t *cr, int x, int y, double r, double g, double b){
	cairo_set_source_rgb (cr, r, g, b);
	cairo_rectangle(cr, x, y, PIXEL_SIZE, PIXEL_SIZE);
	cairo_fill (cr);
}

void paint_pixel(cairo_t *cr, double x, double y){
	double transf = SIZE/STEP_SIZE;
	x = x*PIXEL_SIZE/STEP_SIZE;
	y = y*PIXEL_SIZE/STEP_SIZE;
	//std::cout << x << ":" << y << std::endl;
	std::complex<double> z(x,y);
	std::complex<double> one(1,0);
	std::complex<double> three(3,0);

	for (int i = 0; i < iterations; ++i)
	{
		z = z - (z*z*z-one)/(three*z*z);
	}
	double rl = std::abs(z - red);
	double gl = std::abs(z - green);
	double bl = std::abs(z - blue);
	if (rl <= gl && rl <= bl)
	{
		put_pixel(cr,x+transf,y+transf,1,0,0);
		return;
	}

	if (gl <= rl && gl <= bl)
	{
		put_pixel(cr,x+transf,y+transf,0,1,0);
		return;
	}

	if (bl <= gl && bl <= rl)
	{
		put_pixel(cr,x+transf,y+transf,0,0,1);
		return;
	}
}

void newton(std::string filename) {
	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMAGE_PIXEL_SIZE, IMAGE_PIXEL_SIZE);
	cairo_t *cr = cairo_create (surface); 
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb (cr, 0, 0, 0);

	for (double a = -SIZE; a < SIZE; a += STEP_SIZE)
	{
		for (double b = -SIZE; b < SIZE; b += STEP_SIZE)
		{
			paint_pixel(cr,a,b);
		}
	}

	cairo_destroy (cr);
	cairo_surface_write_to_png (surface, filename.c_str());
	cairo_surface_destroy (surface);
}
int main(int argc, char const *argv[])
{
	newton("A.png");
	return 0;
}



#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <cairo/cairo.h>


const int PIXEL_SIZE = 2;
const int NUMBER_OF_LINES = 8;
const double RADIUS = 50;

const double IMAGE_SIZE = RADIUS*2*PIXEL_SIZE;
const double IMAGE_PIXEL_SIZE = IMAGE_SIZE*1.1;
const double MIDDLE = IMAGE_SIZE/2;

using Point =std::pair<double,double>  ;

void put_pixel(cairo_t *cr, int x, int y, double r, double g, double b){
	cairo_set_source_rgb (cr, r, g, b);
	cairo_rectangle(cr, x, y, PIXEL_SIZE, PIXEL_SIZE);
	cairo_fill (cr);
}


std::vector<Point> symetric_polygon(double number_of_sides, double radius ){
	std::vector<Point> ret;

	double x = IMAGE_SIZE/2;
double 	y = IMAGE_SIZE/2;
	double angle =  360 /number_of_sides ; 
	double direction = 180;
	for (int i = 0; i < number_of_sides; ++i)
	{
		direction += angle;
		double dest_x =  x + radius * std::sin(direction * M_PI / 180);
		double dest_y =  y + radius * std::cos(direction * M_PI / 180);
		ret.push_back(std::make_pair(dest_x,dest_y));
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	std::vector<Point> points = symetric_polygon(NUMBER_OF_LINES,RADIUS);

	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMAGE_PIXEL_SIZE, IMAGE_PIXEL_SIZE);
	cairo_t *cr = cairo_create (surface); 
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb (cr, 0, 0, 0);
	for (auto i = points.begin(); i != points.end(); ++i)
	{
		put_pixel(cr,i->first,i->second, 0,0,0);
		cairo_stroke (cr);
	}

	cairo_destroy (cr);
	cairo_surface_write_to_png (surface, "1.png");
	cairo_surface_destroy (surface);
	return 0;
}

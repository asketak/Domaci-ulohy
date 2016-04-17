#include <iostream>
#include <cmath>
#include <vector>
#include <cairo/cairo.h>


void put_pixel(cairo_t *cr, int x, int y, double r, double g, double b){
	cairo_set_source_rgb (cr, r, g, b);
	cairo_rectangle(cr, x, y, 1, 1);
	cairo_fill (cr);
}
const int RECTANGLE_SIZE = 15;
const int RECTANGLES = 20;
const int IMAGE_PIXEL_SIZE = RECTANGLES * RECTANGLE_SIZE;
const int circles = 4;
const double max_circle = IMAGE_PIXEL_SIZE/2;

void drawdata(cairo_t *cr, int (&black_points)[IMAGE_PIXEL_SIZE][IMAGE_PIXEL_SIZE]){
	for (int x = 0; x < IMAGE_PIXEL_SIZE; ++x)
	{
		for (int y = 0; y < IMAGE_PIXEL_SIZE; ++y)
		{
			if (black_points[x][y] == 1)
			{	
				put_pixel(cr, x, y, 0,0,0);
			}
		}
	}
}
void draw_first(std::string filename){

	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMAGE_PIXEL_SIZE, IMAGE_PIXEL_SIZE);
	cairo_t *cr = cairo_create (surface); 
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb (cr, 0, 0, 0);
	int picture[IMAGE_PIXEL_SIZE][IMAGE_PIXEL_SIZE];

	for (int x = 0; x < IMAGE_PIXEL_SIZE; ++x)
	{
		for (int y = 0; y < IMAGE_PIXEL_SIZE; ++y)
		{
			int temp = x/RECTANGLE_SIZE + y/RECTANGLE_SIZE;
			if (temp % 2 == 0)
			{
				picture[x][y] = 1;
			}
		}
	}

	for (int z = 1; z <= circles; ++z)
	{
		for (int x = 0; x < IMAGE_PIXEL_SIZE; ++x)
		{
			for (int y = 0; y < IMAGE_PIXEL_SIZE; ++y)
			{
				double circ = max_circle * (z+1) / circles;
				bool inside = std::pow(x - IMAGE_PIXEL_SIZE/2,2) + std::pow(y - IMAGE_PIXEL_SIZE/2,2) < std::pow(circ,2);
//				std::cout << circ << std::endl;
				if (inside)
				{
					//std::cout << "INSIDE" << std::endl;
					picture[x][y] = std::abs(picture[x][y]-1);
				}
			}
		}
	}
	

	drawdata(cr, picture);
	cairo_destroy (cr);
	cairo_surface_write_to_png (surface, filename.c_str());
	cairo_surface_destroy (surface);


}
void draw_second(std::string filename){

	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMAGE_PIXEL_SIZE, IMAGE_PIXEL_SIZE);
	cairo_t *cr = cairo_create (surface); 
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb (cr, 0, 0, 0);
	int picture[IMAGE_PIXEL_SIZE][IMAGE_PIXEL_SIZE];
	int circles = 5;
	double circles_width = IMAGE_PIXEL_SIZE/2/circles;

	for (int x = 0; x < IMAGE_PIXEL_SIZE; ++x)
	{
		for (int y = 0; y < IMAGE_PIXEL_SIZE; ++y)
		{
			picture[x][y] = 0;
		}
	}
	for (int z = 1; z <= circles; ++z)
	{
		for (int x = 0; x < IMAGE_PIXEL_SIZE; ++x)
		{
			for (int y = 0; y < IMAGE_PIXEL_SIZE; ++y)
			{

				double circ =  z * circles_width;
				bool inside = std::pow(x - IMAGE_PIXEL_SIZE/2,2) + std::pow(y - IMAGE_PIXEL_SIZE/2,2) < 1.13 * std::pow(circ,2)
				&& std::pow(x - IMAGE_PIXEL_SIZE/2,2) + std::pow(y - IMAGE_PIXEL_SIZE/2,2) > 0.90 * std::pow(circ,2);
				if (inside)
				{
					picture[x][y] = 1;
				}
			}
		}
	}
	for (int x = 0; x < IMAGE_PIXEL_SIZE; ++x)
	{
		for (int y = 0; y < IMAGE_PIXEL_SIZE; ++y)
		{
			if (x < 4./5 * IMAGE_PIXEL_SIZE && x > 1./5 * IMAGE_PIXEL_SIZE && y > 1./5 * IMAGE_PIXEL_SIZE && y < 4./5 * IMAGE_PIXEL_SIZE )
			{
				std::cout << "INSIDE" << std::endl;
				picture[x][y] = std::abs(picture[x][y]-1);
			}
		}
	}

	drawdata(cr, picture);
	cairo_surface_write_to_png (surface, filename.c_str());
	cairo_destroy (cr);
//	cairo_surface_write_to_png (surface, filename.c_str());
	cairo_surface_destroy (surface);


}

int main(int argc, char const *argv[])
{
	//draw_first("effect1.png");
	draw_second("effect2.png");
	//draw_third("effect3.png");

	
	return 0;
}
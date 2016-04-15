#include <iostream>
#include <cmath>
#include <cairo/cairo.h>

void put_pixel(cairo_t *cr, int x, int y, double r, double g, double b){
	cairo_set_source_rgb (cr, r, g, b);
	cairo_rectangle(cr, x, y, 3, 3);
	cairo_fill (cr);
}


void circle_empty(cairo_t *cr, int mid_x, int mid_y)
{
	double size = 80;
	for (int x = -size; x < size; ++x)
	{
		for (int y = -size; y < size; ++y)
		{
			bool inside = std::pow(x ,2) + std::pow(y ,2) < size*size;  
			bool inside2 = std::pow(x ,2) + std::pow(y ,2) > size*size*0.7;  
			if (inside && inside2)
			{
				put_pixel(cr,mid_x + x, mid_y + y,0,0,0);
			}
		}
	}
}

void circle_filled(cairo_t *cr, int mid_x, int mid_y)
{
	double size = 80;
	for (int x = -size; x < size; ++x)
	{
		for (int y = -size; y < size; ++y)
		{
			bool inside = std::pow(x ,2) + std::pow(y ,2) < size*size;  
			if (inside)
			{
				put_pixel(cr,mid_x + x, mid_y + y,0,0,0);
			}
		}
	}
}


void spiral_color(cairo_t *cr, int mid_x, int mid_y)
{
	double size = 100;
	double len = 1000;
	int direction = 90;
	double x  = 0;
	double y  = 0;
	for (int i = 0; i < len; ++i)
	{
		size *= 0.995;
		direction += 2;
		x =  mid_x + size * std::sin(direction * M_PI / 180);
		y =  mid_y + size * std::cos(direction * M_PI / 180);
		double b = std::abs(std::sin(direction * M_PI /180));
		double g = std::sin(direction * M_PI /180);
		double r = 1-g;
		put_pixel(cr,x, y,r,g,b);
	}
}

int main(int argc, char const *argv[])
{
	const int IMAGE_PIXEL_SIZE = 1000;
	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMAGE_PIXEL_SIZE, IMAGE_PIXEL_SIZE);
	cairo_t *cr = cairo_create (surface); 
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb (cr, 0, 0, 0);
	
	circle_filled(cr, IMAGE_PIXEL_SIZE/4, IMAGE_PIXEL_SIZE/4);
	circle_empty(cr, IMAGE_PIXEL_SIZE/2, IMAGE_PIXEL_SIZE/4);
	spiral_color(cr, IMAGE_PIXEL_SIZE * 3/4.0, IMAGE_PIXEL_SIZE/4);
	triangle_color(cr, IMAGE_PIXEL_SIZE/4, IMAGE_PIXEL_SIZE*3/4);
	//elipse(cr);
	//turtle.save("A.png")

	cairo_destroy (cr);
	cairo_surface_write_to_png (surface, "circle.png");
	cairo_surface_destroy (surface);

	

	return 0;
}
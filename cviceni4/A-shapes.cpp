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


void triangle_color(cairo_t *cr, int mid_x, int mid_y)
{
	double half_size = 100;
	double perpendicle_size = std::sqrt(3)*half_size;
	double direction = std::sqrt(3);
	double x0 = mid_x - half_size*2;
	double y0 = mid_y - perpendicle_size;
	double maxx = mid_x + 2*half_size;
	double maxy = mid_y + perpendicle_size/2;
	for (int x = x0; x < maxx; ++x)
	{
		for (int y = y0; y < maxy; ++y)
		{
			if (std::abs(y - y0) >= std::abs(x - mid_x)*direction)  
			{
			double r =  (x-x0)/(maxx - x0) ;
			double g = 1-r;
			double b =  (y-y0)/(maxy - y0) ;
			put_pixel(cr,x, y,r,g,b);
			}
		}
	}
}

void elipse(cairo_t *cr, int mid_x, int mid_y)
{
	double half_size = 300;
	double x0 = mid_x - half_size;
	double y0 = mid_y - half_size;
	double maxx = mid_x + half_size;
	double maxy = mid_y + half_size;
	std::pair<double,double> ohnisko1 = std::make_pair(mid_x+half_size/5,mid_y - half_size / 5);
	std::pair<double,double> ohnisko2 = std::make_pair(mid_x-half_size/5,mid_y + half_size / 5);
	for (int x = x0; x < maxx; ++x)
	{
		for (int y = y0; y < maxy; ++y)
		{
			double dist = std::sqrt(std::pow(x-ohnisko1.first,2) + std::pow(y-ohnisko1.second,2) );
			dist += std::sqrt(std::pow(x-ohnisko2.first,2) + std::pow(y-ohnisko2.second,2) );
			
			std::cout << dist<< std::endl;	
			if (dist < half_size)
			{
			double shade = dist/half_size;
			shade *= shade;
			put_pixel(cr,x, y,shade,shade,shade);
			}
		}
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
	triangle_color(cr, IMAGE_PIXEL_SIZE/4, IMAGE_PIXEL_SIZE*3.0/4);
	elipse(cr, IMAGE_PIXEL_SIZE*3.0/4, IMAGE_PIXEL_SIZE*3/4);

	cairo_destroy (cr);
	cairo_surface_write_to_png (surface, "shapes.png");
	cairo_surface_destroy (surface);
	
	return 0;
}
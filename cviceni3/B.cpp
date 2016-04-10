#include "turtle.h"

void pentagram_absolute(std::string file_name) {

	const int STEP_SIZE = 5 ;
	const int IMAGE_SIZE = 30 ;
	const int IMAGE_PIXEL_SIZE = STEP_SIZE * IMAGE_SIZE;
	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMAGE_PIXEL_SIZE, IMAGE_PIXEL_SIZE);
	cairo_t *cr = cairo_create (surface); 
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb (cr, 0, 0, 0);
	double x = IMAGE_SIZE/2;
	double y = IMAGE_SIZE/2;
	int direction = 180;
	double dest_x =  x + STEP_SIZE * std::sin(direction * M_PI / 180);
	double dest_y =  y + STEP_SIZE * std::cos(direction * M_PI / 180);
	const int steps = 8;
	double angle = 360/5;

	for (int n = 0; n < 5; ++n)
	{
		direction += angle;
		dest_x =  x + steps * std::sin(direction * M_PI / 180);
		dest_y =  y + steps * std::cos(direction * M_PI / 180);
		cairo_move_to (cr, x*STEP_SIZE, y*STEP_SIZE);
		cairo_line_to (cr, dest_x*STEP_SIZE,dest_y*STEP_SIZE);
		cairo_stroke (cr);
		x = dest_x;
		y = dest_y;
	}

	for (int n = 0; n < 5; ++n)
	{
		direction += angle;
		dest_x =  x + steps * std::sin(direction * M_PI / 180);
		dest_y =  y + steps * std::cos(direction * M_PI / 180);
		direction += angle;
		dest_x =  dest_x + steps * std::sin(direction * M_PI / 180);
		dest_y =  dest_y + steps * std::cos(direction * M_PI / 180);
		cairo_move_to (cr, x*STEP_SIZE, y*STEP_SIZE);
		cairo_line_to (cr, dest_x*STEP_SIZE,dest_y*STEP_SIZE);
		cairo_stroke (cr);
		x = dest_x;
		y = dest_y;
	}

	cairo_destroy (cr);
	cairo_surface_write_to_png (surface, file_name.c_str());
	cairo_surface_destroy (surface);	

}

int main(int argc, char const *argv[])
{
	pentagram_absolute("pentagram-absolute.png");
//	pentagram_relative("pentagram-relative.png");
//
//	square_spiral("square_spiral.png");
//	sieve("sieve.png");
//	psycho_triangles("psycho_triangles.png");
//	flower("flower.png");

	return 0;
}


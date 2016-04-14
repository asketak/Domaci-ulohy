#include "turtle.h"
#include <cmath>

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
		double dest2_x =  dest_x + steps * std::sin((direction+angle) * M_PI / 180);
		double dest2_y =  dest_y + steps * std::cos((direction+angle) * M_PI / 180);
		cairo_move_to (cr, x*STEP_SIZE, y*STEP_SIZE);
		cairo_line_to (cr, dest_x*STEP_SIZE,dest_y*STEP_SIZE);
		cairo_stroke (cr);
		cairo_move_to (cr, x*STEP_SIZE, y*STEP_SIZE);
		cairo_line_to (cr, dest2_x*STEP_SIZE,dest2_y*STEP_SIZE);
		cairo_stroke (cr);
		x = dest_x;
		y = dest_y;
	}

	cairo_destroy (cr);
	cairo_surface_write_to_png (surface, file_name.c_str());
	cairo_surface_destroy (surface);	

}

void pentagram_relative (std::string file_name){

	Turtle turtle (25,25,50);
	int angle = 180 - 180/5;
	turtle.pendown();
	for (int x = 0; x < 5; ++x)
	{
		turtle.left(angle);
		turtle.forward(8);
	}
		turtle.left(180-angle);
	angle =  360 /5 ; 
	for (int x = 0; x < 5; ++x)
	{
		turtle.left(angle);
		turtle.forward(5);
	}
	turtle.save(file_name);
}

void square(Turtle *turtle, double size){
	turtle->pendown();
	for (int x = 0; x < 4; ++x)
	{
		turtle->right(90);
		turtle->forward(size);
	}
		turtle->right(90);
}

void square_spiral(std::string file_name){
	const int count_of_spirals = 2;
	double rectangle_size = 20;
	Turtle turtle(50,50,100);
	for (int i = 0; i < count_of_spirals; ++i)
	{
		square(&turtle,rectangle_size);
		turtle.forward(rectangle_size*3/4);
		double angle = atan(1.0/3) * 180.0/ M_PI;
		turtle.left(angle );
		rectangle_size = std::sqrt(std::pow(rectangle_size/4.0,2) + std::pow(rectangle_size*3.0/4,2));
	}
	turtle.save(file_name);
}

void compute_boundaries(double x, float * boundary, int IMAGE_PIXEL_SIZE) {
	double true_x = std::abs(x - IMAGE_PIXEL_SIZE/2);
	double temp2 = 1.0-std::pow(true_x/IMAGE_PIXEL_SIZE*2,2);
	double temp = std::sqrt(temp2);
	*boundary = (IMAGE_PIXEL_SIZE - temp*IMAGE_PIXEL_SIZE)/2;

}
void sieve(std::string file_name){
	const int COUNT_OF_LINES = 10;
	const int PADDING = 10 ;
	const int IMAGE_PIXEL_SIZE = PADDING * COUNT_OF_LINES;
	const int EDGE_SIZE = 13;

	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMAGE_PIXEL_SIZE, IMAGE_PIXEL_SIZE);
	cairo_t *cr = cairo_create (surface); 
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb (cr, 0, 0, 0);
	for (int i = 0; i < COUNT_OF_LINES; ++i)
	{
		float boundary = 0;
		compute_boundaries(PADDING*i+1, &boundary,IMAGE_PIXEL_SIZE);
		boundary += EDGE_SIZE;
		std::cout << "data:" << boundary << std::endl;
		cairo_move_to (cr, PADDING*i,boundary );
		cairo_line_to (cr, PADDING*i,IMAGE_PIXEL_SIZE-boundary);
		cairo_stroke (cr);
		cairo_move_to (cr, boundary,PADDING*i );
		cairo_line_to (cr, IMAGE_PIXEL_SIZE-boundary,PADDING*i);
		cairo_stroke (cr);
	}
	cairo_destroy (cr);
	cairo_surface_write_to_png (surface, file_name.c_str());
	cairo_surface_destroy (surface);	

}

int main(int argc, char const *argv[])
{
	pentagram_absolute("pentagram-absolute.png");
	pentagram_relative("pentagram-relative.png");
	square_spiral("square_spiral.png");
		sieve("sieve.png");
//	psycho_triangles("psycho_triangles.png");
//	flower("flower.png");

	return 0;
}


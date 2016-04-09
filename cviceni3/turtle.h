#include <iostream>
#include <cmath>
#include <cairo/cairo.h>

class Turtle
{
	const int STEP_SIZE = 10;
	double x = 0;
	double y = 0;
	int direction = 180;
	cairo_surface_t *surface;
	cairo_t *cr; 
	bool pendown_flag = false;

public:
	Turtle(int x, int y, const int IMAGE_SIZE) : x(x), y(y){
		surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMAGE_SIZE*STEP_SIZE, IMAGE_SIZE*STEP_SIZE);
		cr = cairo_create (surface); 
		cairo_set_source_rgb (cr, 1, 1, 1);
		cairo_paint(cr);
		cairo_set_source_rgb (cr, 0, 0, 0);
	}
	~Turtle(){
	cairo_destroy (cr);
	cairo_surface_destroy (surface);
}

	void penup(){
		pendown_flag = false;
	}

	void pendown(){
		pendown_flag = true;
	}

	void forward(int steps){
			cairo_move_to (cr, x*STEP_SIZE, y*STEP_SIZE);
			double dest_x =  x + steps * std::sin(direction * M_PI / 180);
			double dest_y =  y + steps * std::cos(direction * M_PI / 180);
			//std::cout << "dest" << direction << ":" << dest_x << ":" << dest_y << std::endl;
			if (pendown_flag)
			{
				cairo_line_to (cr, dest_x*STEP_SIZE,dest_y*STEP_SIZE);
				cairo_stroke (cr);
			}
			x = dest_x;
			y = dest_y;
	}

	void left(int angle){
		direction += angle;	
	}

	void right(int angle){
		left(-angle);
	}

	void back(int angle){
		forward(-angle);
	}

	void save(std::string file_name){
		cairo_surface_write_to_png (surface, file_name.c_str());
	}



};

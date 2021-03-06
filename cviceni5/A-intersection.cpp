#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <cairo/cairo.h>


const int NUMBER_OF_LINES = 4;
const double LINES_LENGHT = 30;

using point =std::pair<double,double>  ;

std::pair<point,point> generate_line(double d){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-d, d);
	std::uniform_real_distribution<> dis90(0,180);
	double x = dis(gen);
	double y = dis(gen); 
	double direction = dis90(gen);
	std::cout << "direction" << direction << std::endl;
	double dest_x  =  x + d/2.0 * std::sin(direction * M_PI / 180);
	double dest_y  =  y + d/2.0 * std::cos(direction * M_PI / 180);
	double start_x =  x - d/2.0 * std::sin(direction * M_PI / 180);
	double start_y =  y - d/2.0 * std::cos(direction * M_PI / 180);
	point px = std::make_pair(start_x, start_y);
	point py = std::make_pair(dest_x, dest_y);
	return std::make_pair(px,py);
}

std::vector<std::pair<point,point>> generate_n_lines(int n, double d){
	std::vector<std::pair<point,point>> ret;
	for (int i = 0; i < n; ++i)
	{
		ret.push_back(generate_line(d));
	}
	return ret;
}

std::vector<point> find_intersections(std::vector<std::pair<point,point>> lines ){
	std::vector<point> ret;
	double inter_x = 0;
	double inter_y = 0;
	for (auto a = lines.begin(); a != lines.end(); ++a)
	{
		for (auto b = a; b != lines.end(); ++b)
		{
			double x1 = a->first.first;
			double y1 = a->first.second;
			double x2 = a->second.first;
			double y2 = a->second.second;
			double x3 = b->first.first;
			double y3 = b->first.second;
			double x4 = b->second.first;
			double y4 = b->second.second;
			if ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4) != 0)
			{
				std::cout << "inif";
				inter_x = ((x1*y2-y1*x2)*(x3-x4)-(x1-x2)*(x3*y4 - y3*x4)) / ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
				inter_y = ((x1*y2-y1*x2)*(y3-y4)-(y1-y2)*(x3*y4 - y3*x4)) / ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
				if ((inter_x > std::min(x1,x2) && inter_x > std::min(x3,x4) && inter_x < std::max(x1,x2) && inter_x < std::max(x3,x4)  )
					&& (inter_y > std::min(y1,y2) && inter_y > std::min(y3,y4) && inter_y < std::max(y1,y2) && inter_y < std::max(y3,y4)  ))
				{
					ret.push_back(std::make_pair(inter_x,inter_y));
				}
			}
		}
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	std::vector<std::pair<point,point>> lines =  generate_n_lines(NUMBER_OF_LINES,LINES_LENGHT);
	std::vector<point> intersections = find_intersections(lines);

	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, LINES_LENGHT*2, LINES_LENGHT*2);
	cairo_t *cr = cairo_create (surface); 
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb (cr, 0, 0, 0);
	std::cout << "LINES START" << std::endl;
	for (auto i = lines.begin(); i != lines.end(); ++i)
	{
		cairo_move_to (cr, i->first.first+LINES_LENGHT, i->first.second+LINES_LENGHT);
		cairo_line_to (cr, i->second.first+LINES_LENGHT, i->second.second+LINES_LENGHT);
		cairo_stroke (cr);
		std::cout << i->first.first << ":"<< i->first.second << "       "<< i->second.first << ":"<< i->second.second << std::endl;
	}
	std::cout << "LINES END" << std::endl;
	std::cout << "INTERSECTIONS START" << std::endl;

	for (auto i = intersections.begin(); i != intersections.end(); ++i)
	{
		std::cout << i->first << ":"<< i->second << std::endl;
	}
	std::cout << "INTERSECTIONS START" << std::endl;
	    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "1.png");
    cairo_surface_destroy (surface);
	return 0;
}
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <cairo/cairo.h>


const int NUMBER_OF_POINTS = 10;


const int IMAGE_SIZE = 1000;
const int BORDER = IMAGE_SIZE / 20;

using point =std::pair<double,double>  ;

point generate_point(){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0+BORDER, IMAGE_SIZE-BORDER);
	double x = dis(gen);
	double y = dis(gen); 
	return std::make_pair(x,y);
}

std::vector<point> generate_n_points(int n){
	std::vector<point> ret;
	for (int i = 0; i < n; ++i)
	{
		ret.push_back(generate_point());
	}
	return ret;
}

std::vector<std::pair<point,point>> find_triangulation(std::vector<point> points ){
	std::vector<std::pair<point,point>> ret;
	for (auto a = points.begin(); a != points.end(); ++a)
	{
		for (auto b = points.begin(); b != points.end(); ++b)
		{

			double x1 = a->first;
			double y1 = a->second;
			double x2 = b->first;
			double y2 = b->second;
			bool intersection_flag = false;
			for (auto i = ret.begin(); i != ret.end(); ++i)
			{
				double x3 = i->first.first;
				double y3 = i->first.second;
				double x4 = i->second.first;
				double y4 = i->second.second;
				if ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4) != 0)
				{
					double inter_x = ((x1*y2-y1*x2)*(x3-x4)-(x1-x2)*(x3*y4 - y3*x4)) / ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
					double inter_y = ((x1*y2-y1*x2)*(y3-y4)-(y1-y2)*(x3*y4 - y3*x4)) / ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
					if ((inter_x > std::min(x1,x2)+0.1 && inter_x > std::min(x3,x4)+0.1 && inter_x < std::max(x1,x2)-0.1 && inter_x < std::max(x3,x4)-0.1  )
						&& (inter_y > std::min(y1,y2)+0.1 && inter_y > std::min(y3,y4)+0.1 && inter_y < std::max(y1,y2)-0.1 && inter_y < std::max(y3,y4)-0.1  ))
					{
						intersection_flag = true;
					}
				}
			}
			if ( !intersection_flag)
			{
				ret.push_back(std::make_pair(*a,*b));
			}
			
		}
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	std::vector<point> points =  generate_n_points(NUMBER_OF_POINTS);
	std::vector<std::pair<point,point>> lines = find_triangulation(points);

	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMAGE_SIZE, IMAGE_SIZE);
	cairo_t *cr = cairo_create (surface); 
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb (cr, 0, 0, 0);
	std::cout << "LINES START" << std::endl;
	for (auto i = lines.begin(); i != lines.end(); ++i)
	{
		cairo_move_to (cr, i->first.first, i->first.second);
		cairo_line_to (cr, i->second.first, i->second.second);
		cairo_stroke (cr);
		std::cout << i->first.first << ":"<< i->first.second << "       "<< i->second.first << ":"<< i->second.second << std::endl;
	}
	std::cout << "LINES END" << std::endl;
	cairo_destroy (cr);
	cairo_surface_write_to_png (surface, "B.png");
	cairo_surface_destroy (surface);
	return 0;
}
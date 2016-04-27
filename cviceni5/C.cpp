#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <cairo/cairo.h>


const int NUMBER_OF_POINTS = 4;


const int IMAGE_SIZE = 100;
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

std::vector<std::pair<point,point>> generate_convex_hull(std::vector<point> points ){
	std::vector<std::pair<point,point>> ret;
	double biggest_y = 0;
	for (auto a = points.begin(); a != points.end(); ++a)
	{
		if (a->second > biggest_y)
		{
			biggest_y = a->second;
		}

	}

		auto this_point = points.begin();
		auto next_point = points.begin();
	do
	{
		double min_angle = 90;
		for (auto a = points.begin(); a != points.end(); ++a)
		{
			double x1 = this_point->first;
			double y1 = this_point->second;
			double x2 = a->first;
			double y2 = a->second;
			double angle =  std::cos(std::atan2((y2-y1) , (x2-x1)));
			std::cout << x1 << ":" << y1  << "_____"<< x2  << ":"<< y2 << " | " << angle << std::endl;

			if (angle < min_angle)
			{
				min_angle = angle;
				next_point = a;
			}
		}
		ret.push_back(std::make_pair(*this_point,*next_point));
		this_point = next_point;
	} while (*this_point != *points.begin());
	return ret;
}

int main(int argc, char const *argv[])
{
	std::vector<point> points =  generate_n_points(NUMBER_OF_POINTS);
	std::vector<std::pair<point,point>> lines = generate_convex_hull(points);

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
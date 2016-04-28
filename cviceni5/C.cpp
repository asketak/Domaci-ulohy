#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <cairo/cairo.h>
#include <algorithm>


const int NUMBER_OF_PointS = 8;


const int IMAGE_SIZE = 100;
const int BORDER = IMAGE_SIZE / 20;

using Point =std::pair<double,double>  ;

Point generate_Point(){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0+BORDER, IMAGE_SIZE-BORDER);
	double x = dis(gen);
	double y = dis(gen); 
	return std::make_pair(x,y);
}

std::vector<Point> generate_n_Points(int n){
	std::vector<Point> ret;
	for (int i = 0; i < n; ++i)
	{
		ret.push_back(generate_Point());
	}
	return ret;
}
//zacatek zkopirovaneho kodu
bool orientation(Point p, Point q, Point r)
{
	int val = (q.second - p.second) * (r.first - q.first) -
	(q.first - p.first) * (r.second - q.second);

    return (val >= 0)? false: true; // clock or counterclock wise
}
//kones zkopirovaneho kodu

std::vector<std::pair<Point,Point>> generate_convex_hull(std::vector<Point> Points ){
	std::vector<std::pair<Point,Point>> ret;
	double smallest_x = IMAGE_SIZE;
	auto this_Point = Points.begin();
	auto next_Point = Points.begin();
	auto start_Point = Points.begin();

	for (auto a = Points.begin(); a != Points.end(); ++a)
	{
		if (a->first < smallest_x)
		{
			this_Point = a;
			start_Point = a;
			next_Point = a;
			smallest_x = a->first;
		}

	}

	do
	{
		next_Point = this_Point+1;
		if (next_Point == Points.end())
		{
			next_Point = Points.begin();
		}
		for (auto a = Points.begin(); a != Points.end(); ++a)
		{
			double x1 = this_Point->first;
			double y1 = this_Point->second;
			double x2 = a->first;
			double y2 = a->second;
			bool orient=  orientation(*this_Point,*a,*next_Point);
			std::cout << x1 << ":" << y1  << "_____"<< x2  << ":"<< y2 << "___" << next_Point->first  << ":"<< next_Point->second << " | " << orient<< std::endl;
			if ( orient )
			{
				next_Point = a;
			}
		}
		ret.push_back(std::make_pair(*this_Point,*next_Point));
		this_Point = next_Point;
	} while (this_Point != start_Point);
	return ret;
}

int main(int argc, char const *argv[])
{
	std::vector<Point> Points =  generate_n_Points(NUMBER_OF_PointS);
	std::vector<std::pair<Point,Point>> lines = generate_convex_hull(Points);

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
	cairo_surface_write_to_png (surface, "C.png");
	cairo_surface_destroy (surface);
	return 0;
}
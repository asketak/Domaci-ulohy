#include <iostream>
#include <cmath>
#include <vector>
#include <cairo/cairo.h>

const int IMAGE_PIXEL_SIZE = 1000;

void put_pixel(cairo_t *cr, int x, int y, double r, double g, double b){
	cairo_set_source_rgb (cr, r, g, b);
	cairo_rectangle(cr, x, y, 3, 3);
	cairo_fill (cr);
}

void drawline(int (&black_points)[IMAGE_PIXEL_SIZE][IMAGE_PIXEL_SIZE], std::pair<double,double> a, std::pair<double,double> b){
	
	std::cout << "DRAWLIN" << std::endl;
	double direction = 0;
	bool vertical_flag = false;
	if (b.first < a.first)
	{
		std::pair<double,double> temp = a;
		a = b;
		b = temp;
	}
	if (b.first != a.first)
	{
		direction = (b.second - a.second) / ( b.first - a.first );
	}else{
		vertical_flag = true;
	}
	for (double x = a.first; x <= b.first; x+=0.01)
	{
		for (int y = a.second; y <= b.second; y++)
		{
			double truy = a.second + (direction*(x-a.first));
				//std::cout << x << ":" << y << ":" << b.first << ":" << b.second << ":" << direction << ":" << truy << std::endl;
	//			std::cout << y << ":" << truy << std::endl;
			if ((y / truy < 1.05 && y / truy > 0.95) || (vertical_flag && x == a.first))
			{
	//std::cout << "PIXEL" << std::endl;cr
				black_points[(int)(x)][y]= 1;
			} 
		}
	}
}

void	drawdata(cairo_t *cr, int (&black_points)[IMAGE_PIXEL_SIZE][IMAGE_PIXEL_SIZE]){
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


void fill_shape(cairo_t *cr, int (&black_points)[IMAGE_PIXEL_SIZE][IMAGE_PIXEL_SIZE]){
	for (int y = 0; y < IMAGE_PIXEL_SIZE; ++y)
	{
		bool inFlag = false;
		bool lineFlag = false;
		int switch_count = 0;
		for (int xx = 0; xx < IMAGE_PIXEL_SIZE; ++xx)
		{
			if (black_points[xx][y] == 1)
			{
				lineFlag = true;
			}
			if (black_points[xx][y] == 0 && lineFlag)
			{
				inFlag = !inFlag;
				lineFlag = false;
				switch_count++;
			}

		}

		inFlag = false;
		lineFlag = false;

		for (int x = 0; x < IMAGE_PIXEL_SIZE && switch_count>1; ++x)
		{



			if (black_points[x][y] == 1)
			{
				lineFlag = true;
			}
			if (black_points[x][y] == 0 && lineFlag)
			{
				inFlag = !inFlag;
				lineFlag = false;
			}
			if (inFlag)
			{
				put_pixel(cr, std::floor(x), y, 0,0,0);
			}
		}

	}
}

void draw_shape(cairo_t *cr, std::vector<std::pair<double,double>> points){
	int picture[IMAGE_PIXEL_SIZE][IMAGE_PIXEL_SIZE];
	std::fill(&picture[0][0], &picture[0][0]+IMAGE_PIXEL_SIZE*IMAGE_PIXEL_SIZE, 0);
	
	for (auto i = points.begin(); i != points.end()-1; ++i)
	{
		drawline(picture, *i,*(i+1));
	}
	drawline(picture, *points.begin(),*(points.end()-1));
	fill_shape(cr,picture);
	drawdata(cr,picture);
}


int main(int argc, char const *argv[])
{
	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMAGE_PIXEL_SIZE, IMAGE_PIXEL_SIZE);
	cairo_t *cr = cairo_create (surface); 
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb (cr, 0, 0, 0);
	std::vector<std::pair<double,double>> points;
	points.push_back(std::make_pair<double,double>(50,50));
	points.push_back(std::make_pair<double,double>(53,300));
	points.push_back(std::make_pair<double,double>(200,300));
	
	draw_shape(cr, points);
	//fill_shape(cr);

	cairo_destroy (cr);
	cairo_surface_write_to_png (surface, "circle.png");
	cairo_surface_destroy (surface);
	
	return 0;
}
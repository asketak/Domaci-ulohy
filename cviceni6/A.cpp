#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <cairo/cairo.h>


const int PIXEL_SIZE = 2;
const int NUMBER_OF_LINES = 3;
const double RADIUS = 200;
const double FRACTION = 1 / 2.0;

const int NUMBER_OF_ITERATIONS = 10000;

const double IMAGE_SIZE = RADIUS*2*PIXEL_SIZE;
const double IMAGE_PIXEL_SIZE = IMAGE_SIZE*1.1;
const double MIDDLE = IMAGE_SIZE/2;

using Point =std::pair<double,double>  ;


const char *colors[] = { // colors to pick from
	"000000", "FFFF00", "1CE6FF", "FF34FF", "FF4A46", "008941", "006FA6", "A30059",
	"FFDBE5", "7A4900", "0000A6", "63FFAC", "B79762", "004D43", "8FB0FF", "997D87",
	"5A0007", "809693", "FEFFE6", "1B4400", "4FC601", "3B5DFF", "4A3B53", "FF2F80",
	"61615A", "BA0900", "6B7900", "00C2A0", "FFAA92", "FF90C9", "B903AA", "D16100",
	"DDEFFF", "000035", "7B4F4B", "A1C299", "300018", "0AA6D8", "013349", "00846F",
	"372101", "FFB500", "C2FFED", "A079BF", "CC0744", "C0B9B2", "C2FF99", "001E09",
	"00489C", "6F0062", "0CBD66", "EEC3FF", "456D75", "B77B68", "7A87A1", "788D66",
	"885578", "FAD09F", "FF8A9A", "D157A0", "BEC459", "456648", "0086ED", "886F4C",

	"34362D", "B4A8BD", "00A6AA", "452C2C", "636375", "A3C8C9", "FF913F", "938A81",
	"575329", "00FECF", "B05B6F", "8CD0FF", "3B9700", "04F757", "C8A1A1", "1E6E00",
	"7900D7", "A77500", "6367A9", "A05837", "6B002C", "772600", "D790FF", "9B9700",
	"549E79", "FFF69F", "201625", "72418F", "BC23FF", "99ADC0", "3A2465", "922329",
	"5B4534", "FDE8DC", "404E55", "0089A3", "CB7E98", "A4E804", "324E72", "6A3A4C",
	"83AB58", "001C1E", "D1F7CE", "004B28", "C8D0F6", "A3A489", "806C66", "222800",
	"BF5650", "E83000", "66796D", "DA007C", "FF1A59", "8ADBB4", "1E0200", "5B4E51",
	"C895C5", "320033", "FF6832", "66E1D3", "CFCDAC", "D0AC94", "7ED379", "012C58"
};

std::vector<std::string> indexcolors(colors, colors + sizeof(colors) / sizeof(colors[0]) ); // definition

void put_pixel(cairo_t *cr, int x, int y, double r, double g, double b){
	cairo_set_source_rgb (cr, r, g, b);
	cairo_rectangle(cr, x, y, PIXEL_SIZE, PIXEL_SIZE);
	cairo_fill (cr);
}


std::vector<Point> symetric_polygon(double number_of_sides, double radius ){
	std::vector<Point> ret;

	double x = IMAGE_SIZE/2;
	double y = IMAGE_SIZE/2;
	double angle =  360 /number_of_sides ; 
	double direction = 180;
	for (int i = 0; i < number_of_sides; ++i)
	{
		direction += angle;
		double dest_x =  x + radius * std::sin(direction * M_PI / 180);
		double dest_y =  y + radius * std::cos(direction * M_PI / 180);
		ret.push_back(std::make_pair(dest_x,dest_y));
	}
	return ret;
}


void get_color(double *r, double *g, double *b, std::string color){
	*r = std::stoi(color.substr(0,2),nullptr,16) / 256.0;
	*g = std::stoi(color.substr(2,2),nullptr,16) / 256.0;
	*b = std::stoi(color.substr(4,2),nullptr,16) / 256.0;
}

void chaos_game(cairo_t *cr, std::vector<Point> points, int iterations) {
	std::vector<Point> tmp;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0,IMAGE_SIZE);
	std::uniform_int_distribution<> point_sel(0,NUMBER_OF_LINES-1);

	Point p = points[0];

	for (int i = 0; i < iterations; ++i)
	{
			int rn = point_sel(gen);
			Point direction = points[rn];
			double dest_x = std::abs(p.first - direction.first) * FRACTION + std::min(p.first,direction.first) ;
			double dest_y = std::abs(p.second - direction.second) * FRACTION + std::min(p.second,direction.second) ;
	//		std::cout << p.first << ":" << p.second << "____" << direction.first << ":" << direction.second << "___" << dest_x << ":" << dest_y << std::endl;
			double r,g,b;
			get_color(&r, &g, &b, indexcolors.at(rn+1));
			put_pixel(cr,dest_x,dest_y,r,g,b);
			p.first = dest_x;
			p.second = dest_y;
	}
}

int main(int argc, char const *argv[])
{

	std::vector<Point> points = symetric_polygon(NUMBER_OF_LINES,RADIUS);

	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMAGE_PIXEL_SIZE, IMAGE_PIXEL_SIZE);
	cairo_t *cr = cairo_create (surface); 
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);
	cairo_set_source_rgb (cr, 0, 0, 0);

	chaos_game(cr, points, NUMBER_OF_ITERATIONS);

	for (auto i = points.begin(); i != points.end(); ++i)
	{
		put_pixel(cr,i->first,i->second, 0,0,0);
		cairo_stroke (cr);
	}

	cairo_destroy (cr);
	cairo_surface_write_to_png (surface, "1.png");
	cairo_surface_destroy (surface);
	return 0;
}

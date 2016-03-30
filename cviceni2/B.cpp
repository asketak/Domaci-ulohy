#include <map>
#include <array>
#include <cmath>
#include <string>
#include <vector>
#include <typeinfo>
#include <cairo/cairo.h>
#include <cassert>
#include <iostream>
#include <boost/lexical_cast.hpp>

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

long long factorial(long long n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

long long combination_number(long long n, long long d){
	return factorial(n) / (factorial(n-d) * factorial(d));

}

void get_color(double *r, double *g, double *b, std::string color){
	*r = std::stoi(color.substr(0,2),nullptr,16) / 256.0;
	*g = std::stoi(color.substr(2,2),nullptr,16) / 256.0;
	*b = std::stoi(color.substr(4,2),nullptr,16) / 256.0;
	std::cout << *r << "::" << *g << "::" << *b << std::endl;
}

void write_pascal(int n, int d, std::string file_name)
{
const int PIXEL_SIZE = 10; 
const int IMAGE_SIZE = PIXEL_SIZE * n;
const int MIDDLE_RECT_START = (IMAGE_SIZE - PIXEL_SIZE) / 2;
assert(d < 256);
assert(PIXEL_SIZE % 2 == 0);

cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMAGE_SIZE, IMAGE_SIZE);
cairo_t *cr = cairo_create (surface); 
cairo_set_source_rgb (cr, 1, 1, 1);
cairo_paint(cr);


	for (int y = 0; y < n; y+= 1) // I have written y lines so fat
	{
		int x = MIDDLE_RECT_START - y*PIXEL_SIZE/2;
		for (int down = 0; down< y; ++down)
		{
			int val = combination_number(y,down) % d;
	std::cout << "value :" << val << std::endl;
			double r,g,b;
			get_color(&r, &g, &b, indexcolors.at(val+1));
			cairo_set_source_rgb (cr, r, g, b);
			cairo_rectangle (cr, x, y*PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE);
	cairo_fill (cr);
			x += PIXEL_SIZE;
		}



	}

	cairo_destroy (cr);
	cairo_surface_write_to_png (surface, file_name.c_str());
	cairo_surface_destroy (surface);

}

int main(int argc, char const *argv[])
{
	write_pascal(10,5, "pascal1.png");
	write_pascal(20,3, "pascal2.png");
	write_pascal(20,7, "pascal3.png");

	return 0;
}
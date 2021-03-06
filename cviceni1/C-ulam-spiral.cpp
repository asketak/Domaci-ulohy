#include <map>
#include <array>
#include <cmath>
#include "gnuplot-iostream/gnuplot-iostream.h"
#include <typeinfo>
#include <cairo/cairo.h>
#include <cassert>

const int PIXEL_SIZE = 10; // one number/point in ulman spiral correspon to PIXEL_SIZE * PIXEL_SIZE rectangle in image
const int SPIRAL_IMAGE_SIZE = 51; // How many rectangles wide the image will be
const int SPIRAL_IMAGE_EDGE_SIZE = SPIRAL_IMAGE_SIZE*PIXEL_SIZE; // Acutal pixel wise size of image
const int MAX_PRIME = SPIRAL_IMAGE_SIZE * SPIRAL_IMAGE_SIZE+1;
const int CENTER_COORDINATE = (SPIRAL_IMAGE_EDGE_SIZE - 1) /2 ;
enum Direction{RIGHT = 1,UP = 2,LEFT =3,DOWN = 4};

Direction turn_left( Direction c ) {
  switch(c) {
    case RIGHT: return UP;
    case UP: return LEFT;
    case LEFT: return DOWN;
    case DOWN: return RIGHT;
  }
}

bool isPrime(int x){
	if (x == 1)
	{
		return false;
	}
	if (x == 2 || x == 3 )
	{
		return true;
	}
	for (int i = 2; i < x; ++i)
	{
		if (x % i == 0)
		{
			return false;
		}
	}
	return true;
}

void write_spiral(std::array<bool, MAX_PRIME> points)
{

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, SPIRAL_IMAGE_EDGE_SIZE, SPIRAL_IMAGE_EDGE_SIZE);
    cairo_t *cr = cairo_create (surface); 

    cairo_set_source_rgb (cr, 128, 128, 128);
    cairo_paint(cr);
    cairo_set_source_rgb (cr, 0, 0, 0);

		int x = CENTER_COORDINATE;
		int y = CENTER_COORDINATE;
		Direction dir = RIGHT;
		int stepCounter = 0;
		int stepLimit = 1;

	for (int i = 1; i < SPIRAL_IMAGE_SIZE*SPIRAL_IMAGE_SIZE; ++i) // for each big pixel in image, draw pixel
	{
		stepCounter++;
		if (points[i])
		{
			cairo_rectangle (cr, x, y, PIXEL_SIZE, PIXEL_SIZE);
		}

		switch (dir)	 {
			case LEFT:
				x -= PIXEL_SIZE;
				break;
			case RIGHT:
				x += PIXEL_SIZE;
				break;
			case UP:
				y -= PIXEL_SIZE;
				break;
			case DOWN:
				y += PIXEL_SIZE;
				break;
		}


		if (stepCounter == stepLimit)
		{
			dir = turn_left(dir);
			stepCounter = 0;
			if (dir == LEFT || dir == RIGHT)
			{
				stepLimit++;
			}

		}

	}

	cairo_fill (cr);
    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "spiral.png");
    cairo_surface_destroy (surface);

}

std::array<bool, MAX_PRIME> fillPrimes(){
	std::array<bool, MAX_PRIME> primes;
	for (int i = 1; i < MAX_PRIME; ++i)
	{
		primes[i] = isPrime(i);
	}
	return primes;
}

int main(int argc, char const *argv[])
{
	assert(SPIRAL_IMAGE_SIZE%2==1);
	std::array<bool, MAX_PRIME> primes = fillPrimes();
	write_spiral(primes);

	return 0;
}
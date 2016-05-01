#include "turtle.h"


void symetric_star(int number_of_sides, const int IMAGE_SIZE, std::string file_name){

	Turtle turtle (IMAGE_SIZE/2,IMAGE_SIZE/2,IMAGE_SIZE);
	int angle = 180 - 180/number_of_sides;
	turtle.pendown();
	for (int x = 0; x < number_of_sides; ++x)
	{
		turtle.left(angle);
		turtle.forward(5);
	}
	turtle.save(file_name);
}

void symetric_polygon(int number_of_sides, const int IMAGE_SIZE, std::string file_name){

	Turtle turtle (IMAGE_SIZE/2,IMAGE_SIZE/2,IMAGE_SIZE);
	int angle =  360 /number_of_sides ; 
	turtle.pendown();
	for (int x = 0; x < number_of_sides; ++x)
	{
		turtle.left(angle);
		turtle.forward(5);
	}
	turtle.save(file_name);
}

int main(int argc, char const *argv[])
{
	symetric_polygon(9,50,"polygon.png");
	symetric_star(5,50,"star.png");

	return 0;
}
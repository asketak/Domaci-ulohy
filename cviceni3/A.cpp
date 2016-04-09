#include "turtle.h"
int main(int argc, char const *argv[])
{
	Turtle turtle (20,20,50);
	turtle.pendown();

	turtle.left(120);
	turtle.forward(5);
	turtle.left(120);
	turtle.forward(5);
	turtle.left(120);
	turtle.forward(5);
	
	turtle.penup();
	turtle.forward(15);
	turtle.pendown();

	turtle.left(90);
	turtle.forward(8);
	turtle.left(90);
	turtle.forward(8);
	turtle.left(90);
	turtle.forward(8);
	turtle.left(90);
	turtle.forward(8);

	turtle.save("turtle.png");

	return 0;
}
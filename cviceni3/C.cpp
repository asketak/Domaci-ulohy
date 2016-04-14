#include "turtle.h"


void bush_recursion(Turtle *turtle, int angle, int deepness, double current_step_size){
	if (deepness == 0)
	{
		return;
	}
	turtle->right(angle);
	turtle->forward(current_step_size);
	bush_recursion(turtle,angle,deepness-1,current_step_size/2);
	turtle->back(current_step_size);
	turtle->left(angle*2);
	turtle->forward(current_step_size);
	bush_recursion(turtle,angle,deepness-1,current_step_size/2);
	turtle->back(current_step_size);
	turtle->right(angle);

}

void bush(int deepness, std::string file_name){
	const double IMAGE_SIZE = std::pow(2,deepness-2); 
	const int angle = 45;

	double current_step_size = IMAGE_SIZE/2;	

	Turtle turtle(IMAGE_SIZE/2,IMAGE_SIZE,IMAGE_SIZE);
	turtle.pendown();
	turtle.forward(current_step_size);
	bush_recursion(&turtle, angle, --deepness,current_step_size/2);
	turtle.save(file_name.c_str());

}

void koch_recursion(Turtle *turtle,int deepness, double current_step_size) {
	const int angle = 60;
	if (deepness == 0)
	{
		std::cout << "TURTLING" << std::endl;
		turtle->forward(current_step_size);
		return;
	}
	koch_recursion(turtle,deepness-1,current_step_size/3);
	turtle->left(angle);
	koch_recursion(turtle,deepness-1,current_step_size/3);
	turtle->right(180-angle);
	koch_recursion(turtle,deepness-1,current_step_size/3);
	turtle->left(angle);
	koch_recursion(turtle,deepness-1,current_step_size/3);
}

void koch(int deepness, std::string file_name){

	double current_step_size = 270;
	double IMAGE_SIZE = current_step_size * 2;

	Turtle turtle(IMAGE_SIZE/3,IMAGE_SIZE*2/3,IMAGE_SIZE);
	turtle.pendown();
	koch_recursion(&turtle, deepness,current_step_size);
	turtle.right(120);
	koch_recursion(&turtle, deepness,current_step_size);
	turtle.right(120);
	koch_recursion(&turtle, deepness,current_step_size);
	turtle.right(120);
	turtle.save(file_name.c_str());

}

int main(int argc, char const *argv[])
{
	bush(10,"bush.png");
	koch(3,"koch.png");

	return 0;
}
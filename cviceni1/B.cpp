#include <map>
#include <vector>
#include <cmath>
#include "gnuplot-iostream/gnuplot-iostream.h"
#include <typeinfo>

std::vector<int> collatz(int n){
	std::vector<int> ret;
	if (n == 0)
	{
		ret.push_back(0);
		return ret;
	}
	while(n != 1){
		ret.push_back(n);
		if (n % 2 == 0)
		{
			n /= 2;
		}else{
			n = n*3 + 1;
		}

	}
	ret.push_back(1);
	return ret;
}

bool pair_compare(const std::pair<int, int>& left, const std::pair<int, int>& right){
	return left.second <  right.second;
};


std::vector<double > collatz_max_number(int MIN_x, int MAX_x){
	std::vector<double > data_points;
	for(double x=MIN_x; x!= MAX_x; x+=1) {
		auto sequence = collatz(x);
		int max_sequence = *std::max_element(sequence.begin(), sequence.end());
		data_points.push_back(max_sequence);
	}
	return data_points;
}

std::vector<std::pair<double, double> > collatz_steps(int MIN_x, int MAX_x){
	std::vector<std::pair<double, double> > data_points;
	for(double x=MIN_x; x!= MAX_x; x+=1) {
		double y = collatz(x).size();
		data_points.push_back(std::make_pair(x, y));
	}
	return data_points;
}

void collatz_graph_steps(int MIN_x, int MAX_x, std::string name){
	auto data_points = collatz_steps(MIN_x, MAX_x);
	auto max_y = std::max_element(data_points.begin(), data_points.end(),pair_compare);
	int y_axis_boost = 1.2 * max_y->second - max_y->second;
	Gnuplot gp;
	gp << "set terminal png "<< "\n"<< " set output \""<< name <<"\"" << "\n";
	gp << "set xrange [" << MIN_x << ":" << MAX_x << "]\nset yrange [0:" << max_y->second + y_axis_boost <<"]\n";
	gp << "plot" << gp.file1d(data_points) << "with points title 'collatz' pt 7" << "\n";
}


void collatz_graph_max_number(int MIN_x, int MAX_x, std::string name){
	std::vector<double >data_points = collatz_max_number(MIN_x, MAX_x);
	auto max_y = *std::max_element(data_points.begin(), data_points.end());
	double y_axis_boost = 1.2 * max_y - max_y;
	Gnuplot gp;
	gp << "set terminal png "<< "\n"<< " set output \""<< name <<"\"" << "\n";
	gp << "set xrange [" << MIN_x << ":" << MAX_x << "]\nset yrange [0:" << max_y + y_axis_boost <<"]\n";
	gp << "plot" << gp.file1d(data_points) << "with points title 'collatz' pt 7" << "\n";
}

int main(int argc, char const *argv[]){
	
	collatz_graph_steps(0,25, "collatz1.png");
	collatz_graph_steps(0,8000, "collatz2.png");

	collatz_graph_max_number(0,25, "collatz-max-1.png");
	collatz_graph_max_number(0,8000, "collatz-max-2.png");

	return 0;
} 
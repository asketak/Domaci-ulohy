#include <map>
#include <vector>
#include <cmath>
#include "gnuplot-iostream/gnuplot-iostream.h"
#include <typeinfo>

int MAX_x = 25;
int MIN_x = 0;

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

int main(int argc, char const *argv[]){
	Gnuplot gp;

	std::vector<std::pair<double, double> > data_points;
	for(double x=MIN_x; x!= MAX_x; x+=1) {
		double y = collatz(x).size();
		data_points.push_back(std::make_pair(x, y));
	}

auto max_y = std::max_element(data_points.begin(), data_points.end(),pair_compare);
         
gp << "set xrange [" << MIN_x << ":" << MAX_x << "]\nset yrange [0:" << max_y->second <<"]\n";
	// Data will be sent via a temporary file.  These are erased when you call
	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
	// and won't be deleted (this is useful when creating a script).

	gp << "plot" << gp.file1d(data_points) << "with points title 'cubic'" << std::endl;
//		<< gp.file1d(xy_pts_B) << "with points title 'circle'" << std::endl;

   return 0;
} 
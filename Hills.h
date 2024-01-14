#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;
//212 - Nazarov - Zakhar

class Hills {
private:
	double x;
	double y;
	double Variance_x;
	double Variance_y;
	double Variance_xy;
	double Height;
public:
	Hills() = default;
	Hills(double x, double y, double Variance_x, double Variance_y, double Height);
	double Gauss_metod(double x0, double y0);
};
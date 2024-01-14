#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;
//212 - Nazarov - Zakhar

class Timber {
private:
	double x1;
	double y1;
	double x2;
	double y2;
	double Radius;
public:
	Timber() = default;
	Timber(double x1, double y1, double x2, double y2, double Radius);
	double barrel(double x0, double y0);
};
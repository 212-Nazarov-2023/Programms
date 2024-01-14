#pragma once
#include <cmath>
using namespace std;
//212 - Nazarov - Zakhar

class Stones {
private:
	double x;
	double y;
	double Radius;
public:
	Stones() = default;
	Stones(double x, double y, double Radius);
	double Sphere(double x0, double y0);
};
#include "Stones.h"
//212 - Nazarov - Zakhar

Stones::Stones(double x, double y, double Radius) 
	: x{ x }, y{ y }, Radius{ Radius } {
}

double Stones::Sphere(double x0, double y0) {
	auto tmp = Radius * Radius - (x - x0) * (x - x0) - (y - y0) * (y - y0);
	return (tmp > 0) ? sqrt(tmp) : 0.0;
}
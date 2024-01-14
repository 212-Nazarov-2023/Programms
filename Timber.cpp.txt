#include "Timber.h"
//212 - Nazarov - Zakhar

Timber::Timber(double x1, double y1, double x2, double y2, double Radius) 
	: x1{ x1 }, y1{ y1 }, x2{ x2 }, y2{ y2 }, Radius{ Radius } {
}

double Timber::barrel(double x0, double y0) {
	double A = y2 - y1;
	double B = x1 - x2;
	double D = A * A + B * B;
    if (D < 1e-11) {
		return 0;
	}
	double C1 = (-y1 * B - x1 * A);
	double C2 = B * (x1 + x2) / 2 - A * (y1 + y2) / 2;
	double d1 = abs(A * x0 + B * y0 + C1) / sqrt(D);
	double d2 = abs(-B * x0 + A * y0 + C2) / sqrt(D);
	if (Radius * Radius > d1 * d1 && D / 4 > d2 * d2) {
		return sqrt(Radius * Radius - d1 * d1);
	}
	return 0;
}

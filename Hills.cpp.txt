#include "Hills.h"
//212 - Nazarov - Zakhar

Hills::Hills(double x, double y, double Variance_x, double Variance_y, double Height)
	: x{ x }, y{ y }, Variance_x{ x }, Variance_y{ y }, Variance_xy{ double(rand() % 10000) / 20000 * Variance_x * Variance_y }, Height{ Height } {
}

double Hills::Gauss_metod(double x0, double y0) {
	auto product = Variance_x * Variance_y;
	double r = Variance_xy / (product);
	return Height * exp(((x - x0) * (x - x0) / (product) + (y - y0) * (y - y0) / (product) - 2 * r * (x - x0) * (y - y0) / (product)) / (2 * r * r - 2));
}
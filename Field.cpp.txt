#include "Field.h"
//212 - Nazarov - Zakhar

Field::Field() : x{ 0 }, y{ 0 } {
	Pixel[0][0] = 0;
}

Field::Field(double x, double y) : x{ 0 }, y{ 0 } {
	Pixel[0][0] = 0;
}

void Field::generate(int g, int k, int b) {
	double x; 
	double y; 
	double Variance_x; 
	double Variance_y; 
	double h; 
	double Radius; 
	double x2; 
	double y2;
	int i;
	srand(time(NULL));
	for (i = 0; i < g; i++) {
		x = double(rand() % 10000) / 10000 * this->x;
		y = double(rand() % 10000) / 10000 * this->y;
		Variance_x = double(rand() % 10000) / 10000 + 0.1;
		Variance_y = double(rand() % 10000) / 10000 + 0.1;
		h = (double(rand() % 10000) / 10000 - 0.3) * sqrt(this->x * this->y);
		G.push_back(Hills(x, y, Variance_x, Variance_y, h));
	}
	for (i = 0; i < k; i++) {
		x = double(rand() % 10000) / 10000 * this->x;
		y = double(rand() % 10000) / 10000 * this->y;
		Radius = double(rand() % 10000) / 10000;
		K.push_back(Stones(x, y, Radius));
	}
	for (i = 0; i < b; i++) {
		x = double(rand() % 10000) / 10000 * this->x;
		y = double(rand() % 10000) / 10000 * this->y;
		x2 = double(rand() % 10000) / 10000 * this->x;
		y2 = double(rand() % 10000) / 10000 * this->y;
		Radius = double(rand() % 10000) / 20000 + 0.1;
		B.push_back(Timber(x, y, x2, y2, Radius));
	}
}

void Field::calculate() {
	unsigned int k;
	double h;
	ofstream fout("Field.txt");
	int size = 128;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			double current_x = i * x / size;
			double current_y = j * y / size;
			h = 0;
			for (k = 0; k < G.size(); k++) {
				h += G[k].Gauss_metod(current_x, current_y);
			}
			for (k = 0; k < K.size(); k++) {
				h += K[k].Sphere(current_x, current_y);
			}
			for (k = 0; k < B.size(); k++) {
				h += B[k].barrel(current_x, current_y);
			}
			fout << current_x << " " << current_y << " " << h << endl;
			Pixel[i][j] = size * h / sqrt(x * y);
		}
		fout << endl;
	}
}
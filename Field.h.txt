#pragma once
#include <time.h>
#include <fstream>
#include <vector>
#include "Stones.h"
#include "Timber.h"
#include "Hills.h"
using namespace std;
//212 - Nazarov - Zakhar

class Field {
private:
	double x;
	double y;
public:
	vector <Hills> G;
	vector <Stones> K;
	vector <Timber> B;
	int Pixel[128][128];
	Field();
	Field(double x, double y);
	void generate(int g, int k, int b);
	void calculate();
};
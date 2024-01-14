#pragma once
#include "Field.h"
//212 - Nazarov - Zakhar

class Rover {
private:
	int Header;
	int Gap;
	double Angle_A;
	double Angle_B;
	int Velocity;
public:
	Field Off_road;
	Rover(int Header, int Gap, double Angle_A, double Angle_B, int Velocity, Field& Off_road);
	Rover();
	int sensor(int x0, int y0, int x, int y);
	int angles(int x0, int y0, int x, int y);
};
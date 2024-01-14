#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "Field.h"
#include "Rover.h"
#include "Processor.h"
using namespace std;
//212 - Nazarov - Zakhar

class Control {
private:
	string Log_control;
	int time;
	int date;
	Field* Off_road;
	Rover* Tracker;
	My_processor* Open_AI;
public:
	Control();
	Control(string Log_control, int time, int date);
	void body(double x, double y, int Hills, int Stones, int Timber, int Header, int Gap, double Angle_A, double Angle_B, int Velocity, int A1, int A2, int B1, int B2);
};
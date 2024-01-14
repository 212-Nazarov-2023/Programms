#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "Control.h"
//212 - Nazarov - Zakhar

using namespace std;

class Boundary {
private:
	string Command;
	string Log_bound;
	Control Client_server;
	int time;
	int date;
public:
	Boundary(string Command, string Log_bound, string Log_control, int time, int date);
	void body();
};


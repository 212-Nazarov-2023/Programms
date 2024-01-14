#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include "Rover.h"
//212 - Nazarov - Zakhar

class My_processor {
private:
	int A1;
	int A2;
	int B1;
	int B2;
	Rover Tracker;
public:
	My_processor(int A1, int A2, int B1, int B2, Rover& Tracker);
	My_processor();
	void route();
};
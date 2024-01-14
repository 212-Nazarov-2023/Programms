#include "Control.h"
//212 - Nazarov - Zakhar

Control::Control() : date{ 0 }, time{ 0 } {
}

Control::Control(string Log_control, int time, int date) : Log_control{ Log_control }, time{ time }, date{ date } {
}

void Control::body(double x, double y, int g, int k, int b, int Header, int Gap, double Angle_A, double Angle_B, int Velocity, int A1, int A2, int B1, int B2) {
	ofstream Log_control_stream(Log_control);
	string field = "launched field";
	string generate = "launched generate";
	string calculate = "launched calculate";
	string rover = "launched rover";
	string processor = "launched processor";
	Log_control_stream << field << endl;
	Off_road = new Field(x, y);
	Log_control_stream << generate << endl;
	(*Off_road).generate(g, k, b);
	Log_control_stream << calculate << endl;
	(*Off_road).calculate();
	Log_control_stream << rover << endl;
	Tracker = new Rover(Header, Gap, Angle_A, Angle_B, Velocity, *Off_road);
	Log_control_stream << processor << endl;
	Open_AI = new My_processor(A1, A2, B1, B2, *Tracker);
	(*Open_AI).route();
	delete Off_road;
	delete Tracker;
	delete Open_AI;
}
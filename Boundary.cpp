#include "Boundary.h"
//212 - Nazarov - Zakhar

Boundary::Boundary(string Command, string Log_bound, string Log_control, int time, int date)
	: Command{ Command }, Log_bound{ Log_bound }, time{ time }, date{ date }, Client_server{ Log_control, time, date } {
}

void Boundary::body() {
	string str;
	string line;
	double x = 10; 
	double y = 10; 
	double Angle_A = 0; 
	double Angle_B = 0;
	int Hills = 0; 
	int Stones = 0; 
	int Timber = 0; 
	int i = 0;
	int Header = 0; 
	int Gap = 0; 
	int Velocity = 0; 
	int A1 = 0; 
	int A2 = 0; 
	int B1 = 0; 
	int B2 = 0;
	ofstream Log_bound(this->Log_bound);
	ifstream Command(this->Command);
	while (getline(Command, line)) {
		istringstream stream(line);
		stream >> str;
		if (str == "field") {
			stream >> x;
			stream >> y;
			Log_bound << "sent field" << endl;
			i++;
		}
		if (str == "generate") {
			stream >> Hills;
			stream >> Stones;
			stream >> Timber;
			Log_bound << "sent generate" << endl;
			i++;
		}
		if (str == "calculate") {
			Log_bound << "sent calculate" << endl;
			i++;
		}
		if (str == "rover") {
			stream >> Header;
			stream >> Gap;
			stream >> Angle_A;
			stream >> Angle_B;
			stream >> Velocity;
			Log_bound << "sent rover" << endl;
			i++;
		}
		if (str == "processor") {
			stream >> A1;
			stream >> A2;
			stream >> B1;
			stream >> B2;
			Log_bound << "sent processor" << endl;
			i++;
		}
	}
	if (i < 5) {
		Log_bound << "ERROR: in command file not enough commands" << endl;
	}
	Client_server.body(x, y, Hills, Stones, Timber, Header, Gap, Angle_A, Angle_B, Velocity, A1, A2, B1, B2);
}
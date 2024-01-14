#include <iostream>
#include <sstream>
#include <string>
#include "Field.h"
#include "Boundary.h"
#include "Hills.h"
#include "Control.h"
#include "Stones.h"
#include "Timber.h"
#include "Rover.h"
#include "Processor.h"


using namespace std;
//212 - Nazarov - Zakhar

int main() {
	int time = 0;
	int date = 0;
	string str;
	string line;
	string Command; 
	string Log_bound;
	string Log_control;
	cout << " Program is looking for the shortest route." << endl;
	cout << " Enter name of the configuration file: ";
	cin >> str;//ввод
	ifstream Config(str);// чтение файла
	while (getline(Config, line)) {//начинаю читать из файла по 1 строке
		istringstream stream(line);// читаю строку через пробелы
		stream >> str;// 1 раз прочитал
		if (str == "command_file") {
			stream >> str;// 2 раз прочитал
			if (str == "=") {
				stream >> Command;//3 раз прочитал и записал в Command
			}
		}
		if (str == "log_boundary") {
			stream >> str;
			if (str == "=") {
				stream >> Log_bound;
			}
		}
		if (str == "log_control") {
			stream >> str;
			if (str == "=") {
				stream >> Log_control;
			}
		}
		if (str == "time") {
			stream >> str;
			if (str == "=") {
				stream >> time;
			}
		}
		if (str == "date") {
			stream >> str;
			if (str == "=") {
				stream >> date;
			}
		}
	}
	Boundary interface(Command, Log_bound, Log_control, time, date);
	interface.body();
}
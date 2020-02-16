#include <wiringPi.h>

#include <vector>
#include <iostream>
#include <thread>
#include <cmath>

#include "WireDataStream.h"

/* Definition */

/* Definition */

bool isEngage;
int triggerCounter;

using namespace std;

WireDataStream stream;

void mainLoop() {
	/*string msg;
	cout << "Enter your command : ";
	cin >> msg;

	if (msg == "start") {
		digitalWrite(PIN_OUT, 1);
		cout << "SIGNAL ON !" << endl;
	}
	else if (msg == "stop"){
		digitalWrite(PIN_OUT, 0);
		cout << "SIGNAL OFF !" << endl;
	}*/
	stream.askAndSendMessage();
	mainLoop();
}

int main(void) {
	mainLoop();
	return 0;
	/*wiringPiSetup();
	//pinMode(PIN_IN, INPUT);
	wiringPiISR(PIN_IN, INT_EDGE_RISING, signalTrigger);
	pinMode(PIN_OUT, OUTPUT);*/
}

/*void signalTrigger() {
	triggerCounter++;
	cout << endl << "Signal Trigger : " << triggerCounter << endl;
}*/
#include "WireDataStream.h"

using namespace std;

/* Constructors & Destructors */
WireDataStream::WireDataStream()
{
	wiringPiSetup();
	pinMode(PIN_IN, INPUT);
	pinMode(PIN_OUT, OUTPUT);
	wiringPiISR(PIN_IN, INT_EDGE_RISING, getSignal);
}
WireDataStream::~WireDataStream()
{
}

/* Methods */
void WireDataStream::askAndSendMessage() {
	string message;
	cout << "Enter the message to be encoded :" << endl;
	getline(cin, message);
	PacketStr packetMSG(message);
	digitalWrite(PIN_OUT, 1);
	sleep(1000); // To synchronize
	digitalWrite(PIN_OUT, 0);
	for (int byte : packetMSG.getLengthInBinary()) {
		digitalWrite(PIN_OUT, byte);
		cout << "[IDX] OUTPUT signal : " << byte << endl;
		sleep(DELAY_TRFT);
	}
	//sleep(DELAY_TRFT-500); // To calculate SIZE
	//Add timing to process size
	for (int byte : packetMSG.getByteArray()) {
		digitalWrite(PIN_OUT, byte);
		cout << "[MSG] OUTPUT signal : " << byte << endl;
		sleep(DELAY_TRFT);
	}
	digitalWrite(PIN_OUT, 0);
}

/* Functions */
void getSignal() {
	cout << "getting Signal..." << endl;
	vector<int> arrayPacket;
	vector<int> arrayPacketSize; //Change with ENCODE_FORMAT
	sleep(DELAY_TRFT);
	for (int byteNb = 0; byteNb < ENCODE_FORMAT; byteNb++) {
		arrayPacketSize.push_back(digitalRead(PIN_IN));
		cout << "[IDX] INPUT Number " << byteNb << "/" << ENCODE_FORMAT - 1 << " : " << digitalRead(PIN_IN) << endl;
		sleep(DELAY_TRFT);
	}
	int packetSize = toInt(arrayPacketSize);
	for (int nbByte = 0; nbByte < packetSize; nbByte++) {
		arrayPacket.push_back(digitalRead(PIN_IN));
		cout << "[MSG] INPUT Number " << nbByte << "/" << packetSize - 1 << " : " << digitalRead(PIN_IN) << endl;
		sleep(DELAY_TRFT);
	}
	cout << "Signal catched !" << endl;
	thread decodeThread(decodeSignal, arrayPacket);
	decodeThread.detach();
}
void decodeSignal(vector<int> arrayPacket) {
	PacketStr packetMSG(arrayPacket);
	cout << "Message : " << packetMSG.getMessage() << endl;
}

void sleep(int delay) {
	struct timespec req = { 0, delay*1000 };
	req.tv_sec = 0;
	req.tv_nsec = delay*1000;
	nanosleep(&req, (struct timespec *)NULL);
}
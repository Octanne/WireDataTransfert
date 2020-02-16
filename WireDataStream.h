#ifndef DEF_WIREDATASTREAM
#define DEF_WIREDATASTREAM

#include <wiringPi.h>
#include <vector>
#include <cmath>
#include <string>
#include <thread>
#include <time.h>

#include "PacketStr.h"

/* Definition */
#define	PIN_OUT	27
#define PIN_IN 26
#define DELAY_TRFT 2000
#define ENCODE_FORMAT 12
/* Definition */

static bool signalIsCome = false;

class WireDataStream
{
public:
	WireDataStream();
	~WireDataStream();

	/* Methods */
	void askAndSendMessage();
protected:
	/* Signal Thread */
	std::thread *waitSignalThread;
};

/* Functions */
void getSignal();
void decodeSignal(std::vector<int> arrayPacket);
void sleep(int delay);

#endif
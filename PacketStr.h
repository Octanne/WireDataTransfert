#ifndef DEF_PACKET
#define DEF_PACKET

#include <vector>
#include <string>
#include <cmath>
#include <iostream>

/* Definition */
#define ENCODE_FORMAT 12

/* Definition */

class PacketStr
{
public:
	PacketStr(std::string message);
	PacketStr(std::vector<int> byteArray);

	/* Methods */
	std::vector<int>& getByteArray();
	std::string& getMessage();
	std::vector<int>& getLengthInBinary();

	/* Default Constructor & Destructor */
	~PacketStr();
	PacketStr();
private:
	int length;
	std::vector<int> byteArray;
	std::vector<int> byteArrayLength;
	std::string message;
};

int toInt(std::vector<int>& byteArray);

#endif

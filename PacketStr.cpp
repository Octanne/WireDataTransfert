#include "PacketStr.h"


/* Constructor & Destructor */
PacketStr::PacketStr()
{

}

PacketStr::PacketStr(std::vector<int> exportByteArray) {
	byteArray = std::vector<int>(exportByteArray);
	length = byteArray.size();
	for (int nbBit = 0; uint(nbBit) < byteArray.size(); nbBit += ENCODE_FORMAT) {
		std::vector<int> charByteArray;
		for (int bit = nbBit; bit < nbBit + ENCODE_FORMAT; bit++) {
			charByteArray.push_back(byteArray.at(bit));
		}
		message += char(toInt(charByteArray));
	}
	//Length
	int lengthInt = length;
	int byteChr[] = { 0,0,0,0,0,0,0,0,0,0,0,0 }; //Change with ENCODE_FORMAT
	int i = 11;
	while (lengthInt > 0) {
		byteChr[i] = lengthInt % 2;
		lengthInt /= 2;
		i--;
	}
	for (int byte : byteChr) {
		byteArrayLength.push_back(byte);
	}
	//Length
}

PacketStr::PacketStr(std::string message) {
	length = message.length()*ENCODE_FORMAT;
	for (char chr : message) {
		int chrInt = int(chr);
		int byteChr[] = {0,0,0,0,0,0,0,0,0,0,0,0}; //Change with ENCODE_FORMAT
		int i = 11;
		while(chrInt > 0) {
			byteChr[i] = chrInt % 2;
			chrInt /= 2;
			i--;
		}
		for (int byte : byteChr) {
			byteArray.push_back(byte);
		}
	}
	//Length
	int lengthInt = length;
	int byteChr[] = { 0,0,0,0,0,0,0,0,0,0,0,0 }; //Change with ENCODE_FORMAT
	int i = 11;
	while (lengthInt > 0) {
		byteChr[i] = lengthInt % 2;
		lengthInt /= 2;
		i--;
	}
	for (int byte : byteChr) {
		byteArrayLength.push_back(byte);
	}
    //Length
	if (uint(length) != byteArray.size()) std::cout << "error length during message encoding!" << std::endl;

}


PacketStr::~PacketStr()
{
}

/* Methods */
std::vector<int>& PacketStr::getByteArray(){
	return byteArray;
}
std::string& PacketStr::getMessage() {
	return message;
}
std::vector<int>& PacketStr::getLengthInBinary() {
	return byteArrayLength;
}

/* Function */
int toInt(std::vector<int> &byteArray) {
	int nb = 0;
	for (int nbr = 0; nbr < int(byteArray.size()); nbr++) {
		if (byteArray.at(nbr)) {
			nb += uint(pow(2, (byteArray.size() - 1 - nbr)));
		}
	}
	return nb;
}
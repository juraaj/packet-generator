#pragma once

#include <string>

using namespace std;

class IPXProtocol
{
private:
	int checksum; 
	int length; // including header
	unsigned char hops;
	unsigned char packet_type; // typ paketu IPX
	string destination_address;
	string source_address;
public:
	IPXProtocol(string destination_address, string source_address, unsigned char packet_type, unsigned char hops, int checksum, int length);
	~IPXProtocol();
};

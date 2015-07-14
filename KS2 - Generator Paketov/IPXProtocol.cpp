#include "IPXProtocol.h"


IPXProtocol::IPXProtocol(string destination_address, string source_address, unsigned char packet_type, unsigned char hops, int checksum, int length)
{
	this->checksum = checksum;
	this->destination_address = destination_address;
	this->hops = hops;
	this->length = length;
	this->packet_type = packet_type;
	this->source_address = source_address;
}


IPXProtocol::~IPXProtocol()
{
}

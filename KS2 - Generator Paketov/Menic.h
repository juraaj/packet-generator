#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <pcap.h>
#include <stdlib.h>
#include <iomanip>

#include "tinyxml.h"

using namespace std;

class Menic
{
private:
	vector<vector<unsigned char>> packets;
	vector<vector<unsigned char>> filtered;
	string SrcIP;
	string DstIP;
	string SrcPort;
	string DstPort;
	string changeSrcIP;
	string changeDstIP;
	string changeSrcPort;
	string changeDstPort;
	void clearParams();
	void getParsedAddress(unsigned char *part1, unsigned char *part2, unsigned char *part3, unsigned char *part4, string address);
	void calculateChecksumTCP_UDP(vector<unsigned char> *packet, string tcp_udp);
	bool checkSrcIP(vector<unsigned char> actualPacket);
	bool checkDstIP(vector<unsigned char> actualPacket);
	bool checkSrcPort(vector<unsigned char> actualPacket);
	bool checkDstPort(vector<unsigned char> actualPacket);
	void filterTCPPackets();
	void filterUDPPackets();
	
	
	void getTCPChangeParams(TiXmlElement *parameter);
	void getUDPCHangeParams(TiXmlElement *parameter);
	
	void getUDPFilteringParams(TiXmlElement *parameter);
	void getTCPFilteringParams(TiXmlElement *parameter);
	void changeUDPPacket(vector<unsigned char> *actualPacket);
	void changeTCPPacket(vector<unsigned char> *actualPacket);
	unsigned char* vectorToBytes(vector<unsigned char> actualPacket);
	void dumpToFile(vector<vector<unsigned char>> filtered, string outFileName);
public:
	Menic();
	
	int filterAndChange(string filename);
	int readBytesFromDump(string filename);
	int readFilterParams(string filename);
	~Menic();
};


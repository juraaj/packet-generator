#pragma once
#include <string>
#include <vector>

#include "tinyxml.h"

using namespace std;

class IRTPMenic
{
private:
	string IRTPType;
	string IRTPPort;
	string IRTPSeqNumber;
	string changeIRTPType;
	string changeIRTPPort;
	string changeIRTPSeqNumber;
	void filterIRTPPackets();
	void getIRTPFilteringParams(TiXmlElement *parameter);
	void getIRTPChangeParams(TiXmlElement *parameter);
public:
	IRTPMenic();
	~IRTPMenic();
};


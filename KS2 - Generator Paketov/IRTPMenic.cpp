#include "IRTPMenic.h"


IRTPMenic::IRTPMenic()
{
}
/*
void IRTPMenic::filterIRTPPackets()
{
	vector<unsigned char> actualPacket;
	int i;

	for (i = 0; i < packets.size(); i++)
	{
		actualPacket = packets[i];
		if ()
		{
			changeTCPPacket(&actualPacket);
			filtered.push_back(actualPacket);
		}

	}
}

void IRTPMenic::getIRTPChangeParams(TiXmlElement *filter_params)
{
	TiXmlElement *element;

	element = filter_params->FirstChildElement("local_address");
	if (element != NULL)
		changeSrcIP = element->GetText();

	element = filter_params->FirstChildElement("remote_address");
	if (element != NULL)
		changeDstIP = element->GetText();

	element = filter_params->FirstChildElement("type");
	if (element != NULL)
		changeIRTPType = element->GetText();

	element = filter_params->FirstChildElement("port");
	if (element != NULL)
		changeIRTPPort = element->GetText();

	element = filter_params->FirstChildElement("seq_number");
	if (element != NULL)
		changeIRTPSeqNumber = element->GetText();
}

void IRTPMenic::getIRTPFilteringParams(TiXmlElement *filter_params)
{
	TiXmlElement *element;

	element = filter_params->FirstChildElement("local_address");
	if (element != NULL)
		SrcIP = element->GetText();

	element = filter_params->FirstChildElement("remote_address");
	if (element != NULL)
		DstIP = element->GetText();

	element = filter_params->FirstChildElement("type");
	if (element != NULL)
		IRTPType = element->GetText();

	element = filter_params->FirstChildElement("port");
	if (element != NULL)
		IRTPPort = element->GetText();

	element = filter_params->FirstChildElement("seq_number");
	if (element != NULL)
		IRTPSeqNumber = element->GetText();
}*/
IRTPMenic::~IRTPMenic()
{
}

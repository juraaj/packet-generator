#include "Menic.h"


Menic::Menic()
{
}

void Menic::clearParams()
{
	SrcIP.clear();
	DstIP.clear();
	SrcPort.clear();
	DstPort.clear();
	changeSrcIP.clear();
	changeDstIP.clear();
	changeSrcPort.clear();
	changeDstPort.clear();
}
void Menic::changeTCPPacket(vector<unsigned char> *actualPacket)
{
	int srcPort, dstPort;

	if (!changeSrcIP.empty());
	if (!changeDstIP.empty());
	if (!changeSrcPort.empty())
	{
		srcPort = atoi(changeSrcPort.c_str());

		actualPacket->at(34) = (unsigned char)srcPort >> 8;
		actualPacket->at(35) = (unsigned char)srcPort & 0xFF;
	}
	if (!changeDstPort.empty())
	{
		dstPort = atoi(changeDstPort.c_str());

		actualPacket->at(36) = (unsigned char)dstPort >> 8;
		actualPacket->at(37) = (unsigned char)dstPort & 0xFF;
	}
}
void Menic::changeUDPPacket(vector<unsigned char> *actualPacket)
{
	int srcPort, dstPort;

	if (!changeSrcIP.empty());
	if (!changeDstIP.empty());
	if (!changeSrcPort.empty())
	{
		srcPort = atoi(changeSrcPort.c_str());

		actualPacket->at(34) = (unsigned char)srcPort >> 8;
		actualPacket->at(35) = (unsigned char)srcPort & 0xFF;
	}
	if (!changeDstPort.empty())
	{
		dstPort = atoi(changeDstPort.c_str());

		actualPacket->at(36) = (unsigned char)dstPort >> 8;
		actualPacket->at(37) = (unsigned char)dstPort & 0xFF;
	}
}
void Menic::getParsedAddress(unsigned char *part1, unsigned char *part2, unsigned char *part3, unsigned char *part4, string address)
{
	string tmp;
	int i, num, endIndex, startIndex;
	vector<int> results;


	tmp = address;
	startIndex = 0;

	for (i = 0; i < 4; i++)
	{
		endIndex = tmp.find_first_of('.', startIndex);
		num = atoi(address.substr(startIndex, endIndex - startIndex).c_str());

		results.push_back(num);
		startIndex = endIndex + 1;
	}

	*part1 = results.at(0); //vratenie premennych
	*part2 = results.at(1);
	*part3 = results.at(2);
	*part4 = results.at(3);

}
void Menic::calculateChecksumTCP_UDP(vector<unsigned char> *packet, string tcp_udp)
{
	int tmp, fifthByte;

	if (!strcmp(tcp_udp.c_str(), "UDP"))
	{
		tmp = packet->at(26) << 8;
		tmp += packet->at(27);
		tmp += packet->at(28) << 8;
		tmp += packet->at(29);
		tmp += packet->at(30) << 8;
		tmp += packet->at(31);
		tmp += packet->at(32) << 8;
		tmp += packet->at(33);

		tmp += 0x11; // protocol
		tmp += 8; //length
		tmp += packet->at(34) << 8;
		tmp += packet->at(35);
		tmp += packet->at(36) << 8;
		tmp += packet->at(37);
		tmp += 8; //

		fifthByte = (tmp & 0xF0000) >> 16;
		tmp = tmp & 0xFFFF;
		tmp += fifthByte;
		tmp = ~tmp & 0xFFFF;

		packet->at(40) =tmp >> 8;
		packet->at(41) =tmp & 0xFF;
	}
	else if (!strcmp(tcp_udp.c_str(), "TCP"))
	{
		tmp = packet->at(26) << 8;
		tmp += packet->at(27);
		tmp += packet->at(28) << 8;
		tmp += packet->at(29);
		tmp += packet->at(30) << 8;
		tmp += packet->at(31);
		tmp += packet->at(32) << 8;
		tmp += packet->at(33);

		tmp += 0x06; // TCP
		tmp += 20; //TCP length

		tmp += packet->at(34) << 8;
		tmp += packet->at(35);
		tmp += packet->at(36) << 8;
		tmp += packet->at(37);

		tmp += 0x5000; // data offser + reserved + flags

		fifthByte = (tmp & 0xF0000) >> 16;
		tmp = tmp & 0xFFFF;
		tmp += fifthByte;
		tmp = ~tmp & 0xFFFF;
	}

}
bool Menic::checkSrcIP(vector<unsigned char> actualPacket)
{
	unsigned char addrPart1, addrPart2, addrPart3, addrPart4;

	if (SrcIP.empty())
		return true;

	getParsedAddress(&addrPart1, &addrPart2, &addrPart3, &addrPart4, SrcIP);

	return (addrPart1 == actualPacket.at(26) &&
			addrPart2 == actualPacket.at(27) &&
			addrPart3 == actualPacket.at(28) &&
			addrPart4 == actualPacket.at(29));
}
bool Menic::checkDstIP(vector<unsigned char> actualPacket)
{
	unsigned char addrPart1, addrPart2, addrPart3, addrPart4;

	if (DstIP.empty())
		return true;

	getParsedAddress(&addrPart1, &addrPart2, &addrPart3, &addrPart4, DstIP);

	return (addrPart1 == actualPacket.at(30) &&
			addrPart2 == actualPacket.at(31) &&
			addrPart3 == actualPacket.at(32) &&
			addrPart4 == actualPacket.at(33));
}
bool Menic::checkSrcPort(vector<unsigned char> actualPacket)
{
	int srcPortInPacket;

	if (SrcPort.empty())
		return true;

	srcPortInPacket = actualPacket.at(34) << 8;
	srcPortInPacket = actualPacket.at(35);

	if (srcPortInPacket == atoi(SrcPort.c_str()))
		return true;

	return false;
}
bool Menic::checkDstPort(vector<unsigned char> actualPacket)
{
	int dstPortInPacket;

	if (DstPort.empty())
		return true;

	dstPortInPacket = actualPacket.at(36) << 8;
	dstPortInPacket = actualPacket.at(37);

	if (dstPortInPacket == atoi(DstPort.c_str()))
		return true;

	return false;
}
void Menic::filterTCPPackets()
{
	vector<unsigned char> actualPacket;
	int i;

	for (i = 0; i < packets.size(); i++)
	{
		actualPacket = packets[i];
		if (checkSrcPort(actualPacket) && checkDstPort(actualPacket) &&
			checkSrcIP(actualPacket) && checkDstIP(actualPacket))
		{
			changeTCPPacket(&actualPacket);
			calculateChecksumTCP_UDP(&actualPacket, "TCP");
			filtered.push_back(actualPacket);
		}

	}
}
void Menic::filterUDPPackets()
{
	vector<unsigned char> actualPacket;
	int i;

	for (i = 0; i < packets.size(); i++)
	{
		actualPacket = packets[i];
		if (checkSrcPort(actualPacket) && checkDstPort(actualPacket) && 
			checkSrcIP(actualPacket) && checkDstIP(actualPacket))
		{
			changeUDPPacket(&actualPacket);
			calculateChecksumTCP_UDP(&actualPacket, "UDP");
			filtered.push_back(actualPacket);
		}
			
	}
}
void Menic::getTCPChangeParams(TiXmlElement *change_parameter)
{
	TiXmlElement *element;

	element = change_parameter->FirstChildElement("local_address");
	if (element != NULL)
		changeSrcIP = element->GetText();

	element = change_parameter->FirstChildElement("remote_address");
	if (element != NULL)
		changeDstIP = element->GetText();

	element = change_parameter->FirstChildElement("local_port");
	if (element != NULL)
		changeSrcPort = element->GetText();

	element = change_parameter->FirstChildElement("remote_port");
	if (element != NULL)
		changeDstPort = element->GetText();
}
void Menic::getUDPCHangeParams(TiXmlElement *change_parameter)
{
	TiXmlElement *element;

	element = change_parameter->FirstChildElement("local_address");
	if (element != NULL)
		changeSrcIP = element->GetText();

	element = change_parameter->FirstChildElement("remote_address");
	if (element != NULL)
		changeDstIP = element->GetText();

	element = change_parameter->FirstChildElement("local_port");
	if (element != NULL)
		changeSrcPort = element->GetText();

	element = change_parameter->FirstChildElement("remote_port");
	if (element != NULL)
		changeDstPort = element->GetText();
}
void Menic::getUDPFilteringParams(TiXmlElement *filter_params)
{
	TiXmlElement *element;
	
	element = filter_params->FirstChildElement("local_address");
	if (element != NULL)
		SrcIP = element->GetText();

	element = filter_params->FirstChildElement("remote_address");
	if (element != NULL)
		DstIP = element->GetText();

	element = filter_params->FirstChildElement("local_port");
	if (element != NULL)
		DstPort = element->GetText();
		
	element = filter_params->FirstChildElement("remote_port");
	if (element != NULL)
		SrcPort = element->GetText();
}
void Menic::getTCPFilteringParams(TiXmlElement *filter_params)
{
	TiXmlElement *element;

	element = filter_params->FirstChildElement("local_address");
	if (element != NULL)
		SrcIP = element->GetText();

	element = filter_params->FirstChildElement("remote_address");
	if (element != NULL)
		DstIP = element->GetText();

	element = filter_params->FirstChildElement("local_port");
	if (element != NULL)
		DstPort = element->GetText();

	element = filter_params->FirstChildElement("remote_port");
	if (element != NULL)
		SrcPort = element->GetText();		
}
int Menic::readBytesFromDump(string filename)
{
	vector <unsigned char> tmp;
	char errbuff[PCAP_ERRBUF_SIZE];
	struct pcap_pkthdr *header;
	const u_char *data;
	int row = 0;

	
	pcap_t *pcap = pcap_open_offline(filename.c_str(), errbuff);


	u_int packetCount = 0;

		while (int returnValue = pcap_next_ex(pcap, &header, &data) >= 0)
		{
			this->packets.push_back(tmp);
			for (u_int i = 0; i < header->caplen; i++)
			{
				this->packets[row].push_back(data[i]);
			}
			printf("\n\n");
			row++;
		}
		return 0;
}
int Menic::readFilterParams(string filename)
{
	TiXmlDocument XmlFile;
	TiXmlElement *configure_summary, *item, *filter_params, *change_params;
	string elementName, parameter;
	string a;


	XmlFile.LoadFile(filename.c_str());
	configure_summary = XmlFile.FirstChildElement();
	
	for (item = configure_summary->FirstChildElement(); item != NULL; item = item->NextSiblingElement())
	{
		clearParams();
		filter_params = item->FirstChildElement("filter_parameters");
		change_params = item->FirstChildElement("change_parameters");
		parameter = filter_params->FirstChildElement("protocol")->GetText();

		if (!strcmp(parameter.c_str(), "TCP"))
		{
			getTCPFilteringParams(filter_params);
			getTCPChangeParams(change_params);
			filterTCPPackets();
		}
		if (!strcmp(parameter.c_str(), "UDP"))
		{
			getUDPFilteringParams(filter_params);
			getUDPCHangeParams(change_params);
			filterUDPPackets();
		}
		if (!strcmp(parameter.c_str(), "IRTP"))
		{
			//getIRTPFilteringParams(filter_params);
			//getIRTPChangeParams(change_params);
			//filterIRTPPackets();
		}

	}

	dumpToFile(filtered, "filtered");
	
	return 1;

}
unsigned char* Menic::vectorToBytes(vector<unsigned char> actualPacket)
{
	int size;
	unsigned char *bytes;

	size = (int)actualPacket.size();
	bytes = new unsigned char[size];

	for (int i = 0; i < size; i++)
		bytes[i] = actualPacket.at(i);


	return bytes;
}
void Menic::dumpToFile(vector<vector<unsigned char>> filtered, string outFileName)
{
	pcap_pkthdr header;
	timeval *ts;
	pcap_t *p;
	pcap_dumper_t *out_file;
	unsigned char *bytes;

	p = pcap_open_dead(1, 65536);
	out_file = pcap_dump_open(p, outFileName.c_str());

	ts = (timeval*)malloc(sizeof(pcap_pkthdr));
	
	for (int i = 0; i < filtered.size(); i++)
	{
		header.caplen = this->filtered.at(i).size();
		header.len = this->filtered.at(i).size();
		header.ts = *ts;
		bytes = vectorToBytes(filtered.at(i));
		pcap_dump((u_char*)out_file, &header, bytes);
	}

}
Menic::~Menic()
{
}

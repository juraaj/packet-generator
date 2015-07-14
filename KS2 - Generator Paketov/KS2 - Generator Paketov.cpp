#include "Generator.h"
#include <string>
#include <iostream>
#include <vector>

#include "Menic.h"

using namespace std;

int main()
{
	Menic menic;
	Generator generator;
	string in_file, out_file;
	
	/*cout << "Zadajte nazov vstupneho suboru vo formate <filename>.xml: ";
	cin >> in_file;
	cout << "Zadajte nazov vystupneho suboru: ";
	cin >> out_file;
	if (!generator.generatePackets("Packets.xml","dump"))
		cout << "Error in parsing." << endl << "Please check your XML." << endl;
	else
		cout << "Packets were succesfully generated in file " << out_file << endl;
	*/

	

	menic.readBytesFromDump("dump");
	menic.readFilterParams("change.xml");

	cout << "Press key to continue...";
	fflush(stdin);
	getchar();
	return 0;
}
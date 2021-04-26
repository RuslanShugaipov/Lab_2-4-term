#include "Encode_N_Decode.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream read;
	read.exceptions(ifstream::failbit);
	try
	{
		//reading lines from the input file, creating an object of the ifstream class
		read.open("Bill Gates quote.txt");

		//reading the text from the file to the string str
		string str, str_add;
		while (!read.eof())
		{
			getline(read, str_add);
			str += str_add;
		}

		//calling the function that processes the input string according to the task
		Encoding_N_Decoding(str);

		read.close();
	}
	catch (const ifstream::failure& e)
	{
		cout << "Exception opening file\n";
	}

	return 0;
}
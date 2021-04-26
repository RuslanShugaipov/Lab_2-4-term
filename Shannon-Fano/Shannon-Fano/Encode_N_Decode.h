#pragma once
#include <iostream>
#include "LinkedList.h"
#include "RB-TREE(DEF).h"
#include <string>
#include <iomanip>

using namespace std;

//a template function that sorts two arrays at once
template<class ARRAY_TYPE_1, class ARRAY_TYPE_2>
void Bubble_Sort(ARRAY_TYPE_1* array_1, ARRAY_TYPE_2* array_2, int Array_Size)
{
	ARRAY_TYPE_1 temp_1;
	ARRAY_TYPE_2 temp_2;

	for (int i = 0; i < Array_Size; ++i)
	{
		for (int j = i + 1; j < Array_Size; ++j)
		{
			if (array_1[i] < array_1[j])
			{
				//data
				temp_1 = array_1[i];
				array_1[i] = array_1[j];
				array_1[j] = temp_1;
				//key
				temp_2 = array_2[i];
				array_2[i] = array_2[j];
				array_2[j] = temp_2;
			}
		}
	}
}

//a template function that looks for a boundary that divides an array into two equal or nearly equal parts
template<class ARRAY_TYPE>
unsigned Search_Border(ARRAY_TYPE* array, int start, int end)
{
	unsigned from_begin = 0, from_end = 0;
	int j = end - 1;

	for (int i = start; ; i++)
	{
		if (i == j)
		{
			return i;
		}
		from_begin += array[i];
		while (true)
		{
			if (from_end < from_begin)
				from_end += array[j--];
			else
				break;
			if (i == j)
			{
				return i;
			}

		}
		if (i == j)
		{
			return i;
		}
	}
}

//a function that implements the Shannon-Fano algorithm using the Search_Border function
void Shannon_Fano(unsigned* freq, char* sym, string& Branch, string& Full_Branch, int start, int end, RB_TREE_Node<char, string>* Symbols_Code, unsigned& Memory_Size_After)
{
	unsigned m;
	string T_Branch = "";

	T_Branch = Full_Branch + Branch;
	if (start == end)
	{
		Memory_Size_After += T_Branch.length() * freq[start];
		Symbols_Code->Insert(sym[start], T_Branch);
		cout << sym[start] << "\t" << freq[start] << "\t\t" << T_Branch << endl;
		return;
	}
	m = Search_Border(freq, start, end);

	string zero = "0", one = "1";
	Shannon_Fano(freq, sym, one, T_Branch, start, m, Symbols_Code, Memory_Size_After);
	Shannon_Fano(freq, sym, zero, T_Branch, m + 1, end, Symbols_Code, Memory_Size_After);
}

//a function that calls within itself a function that implements the Shannon-Fano algorithm, and also outputs the following data:
//the amount of memory that the source and encoded strings occupy, the table of frequencies and character codes, the result of en-
//coding and decoding, the compression ratio
void Encoding_N_Decoding(string& str)
{
	//output the input string/text
	cout << "Input string/text: " << str << "\n\n";

	//variables that contain the size of the string before encoding and after encoding the string
	unsigned Memory_Size_Before = str.length() * 8, Memory_Size_After = 0;

	//creating the Frequency variable to create a map, and then filling it with characters and the frequency of their occurrence
	RB_TREE_Node<char, unsigned> Frequency;
	Frequency.NIL_N_Root();

	//filling the associative array with values from the string/text
	for (int i = 0; i < str.length(); ++i)
	{
		try
		{
			Frequency.Insert(str[i], 1);
		}
		catch (int ex)
		{
			if (ex == -1)
				Frequency[str[i]]++;
		}
	}

	//creating a variable that stores the number of encoded characters for easy use
	unsigned Array_Size = Frequency.Get_Size();

	//creating 2 arrays that will store characters and their frequencies
	unsigned* A = new unsigned[Array_Size];
	char* B = new char[Array_Size];

	//using the added RB_TREE_Node.h of the method, we fill the arrays created earlier with the values of the keys and data of the associative array
	Frequency.Fill_Array(Frequency.Get_Root(), A, "data");
	Frequency.Fill_Array(Frequency.Get_Root(), B, "key");

	//two arrays of characters and their frequencies are sorted at once
	Bubble_Sort(A, B, Array_Size);

	string zero = "";

	RB_TREE_Node<char, string> Symbols_Code;
	Symbols_Code.NIL_N_Root();

	//output the table, size, and coefficient 
	cout << "Symbol:\tFrequency:\tCode:\n";
	Shannon_Fano(A, B, zero, zero, 0, Array_Size - 1, &Symbols_Code, Memory_Size_After);
	cout << "\nSize in bits before encoding: " << Memory_Size_Before << "\n\nSize in bits after encoding: " << Memory_Size_After << endl;
	//the coefficient is calculated as follows: from one, we subtract the quotient of the line size after and before encoding,
	//then multiply by 100 and get the result as a percentage
	cout << "\nCompression ratio: " << round((1 - ((double)Memory_Size_After / (double)Memory_Size_Before)) * 100) << "%\n";

	//we output the result of encoding the string, for further convenience, we put a space between the bits of individual characters
	string Encoding_Result = "";
	//concatenate the strings to get the final string
	for (int i = 0; i < str.length(); i++)
	{
		Encoding_Result += Symbols_Code[str[i]] + " ";
	}
	cout << "\nResult of encoding: " << Encoding_Result << endl;

	//we create an associative array for convenience, since operator overloads were created
	//for the task, spaces were placed between the bits of individual characters
	//in advance, so it is easy to decode a string using overload operators
	RB_TREE_Node<string, char> Codes_Symbol;
	Codes_Symbol.NIL_N_Root();
	for (int i = 0; i < Array_Size; ++i)
	{
		Codes_Symbol.Insert(Symbols_Code[B[i]], B[i]);
	}

	string Decoding_Result = "", Code;
	//concatenate the strings to get the final string
	for (int i = 0; i < Encoding_Result.length(); i++)
	{
		Code = "";
		while (true)
		{
			if (Encoding_Result[i] != ' ')
				Code += Encoding_Result[i++];
			else
				break;
		}
		Decoding_Result += Codes_Symbol[Code];
	}

	cout << "\nResult of decoding: " << Decoding_Result << endl;

	delete[] A;
	delete[] B;
}

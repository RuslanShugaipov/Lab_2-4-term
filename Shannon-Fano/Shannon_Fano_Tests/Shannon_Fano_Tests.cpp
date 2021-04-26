#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\Руслан\source\repos\Shannon-Fano\Shannon-Fano\LinkedList.h"
#include "C:\Users\Руслан\source\repos\Shannon-Fano\Shannon-Fano\RB-TREE(DEF).h"
#include "C:\Users\Руслан\source\repos\Shannon-Fano\Shannon-Fano\Encode_N_Decode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ShannonFanoTests
{
	TEST_CLASS(ShannonFanoTests)
	{
	public:
		
		TEST_METHOD(Bubble_Sorting)
		{
			unsigned* numbers = new unsigned[5] { 1,2,3,4,5 };
			char* letters = new char[5]{ 'a', 'b', 'c', 'd', 'e' };

			unsigned* numbers_check = new unsigned[5]{ 5,4,3,2,1 };
			char* letters_check = new char[5]{ 'e', 'd', 'c', 'b', 'a'};

			Bubble_Sort(numbers, letters, 5);

			for (int i = 0; i < 5; ++i)
			{
				Assert::AreEqual(numbers[i], numbers_check[i]);
				Assert::AreEqual(letters[i], letters_check[i]);
			}
		}

		TEST_METHOD(Border_Search)
		{
			int* numbers = new int[5] { 5,4,3,3,2 };

			int border = Search_Border(numbers, 0, 5);

			Assert::AreEqual(border, 1);
		}

		TEST_METHOD(Algorithm_Shannon_Fano)
		{
			string str = "Hello, world!";

			unsigned Memory_Size_Before = str.length() * 8, Memory_Size_After = 0;

			RB_TREE_Node<char, unsigned> Frequency;
			Frequency.NIL_N_Root();

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

			unsigned Array_Size = Frequency.Get_Size();

			unsigned* A = new unsigned[Array_Size];
			char* B = new char[Array_Size];

			Frequency.Fill_Array(Frequency.Get_Root(), A, "data");
			Frequency.Fill_Array(Frequency.Get_Root(), B, "key");

			Bubble_Sort(A, B, Array_Size);

			string zero = "";

			RB_TREE_Node<char, string> Symbols_Code;
			Symbols_Code.NIL_N_Root();

			Shannon_Fano(A, B, zero, zero, 0, Array_Size - 1, &Symbols_Code, Memory_Size_After);

			RB_TREE_Node<char, string> Symbols_Code_Check;
			Symbols_Code_Check.NIL_N_Root();
			Symbols_Code_Check.Insert('l', "11");
			Symbols_Code_Check.Insert('o', "101");
			Symbols_Code_Check.Insert(' ', "100");
			Symbols_Code_Check.Insert('!', "011");
			Symbols_Code_Check.Insert('H', "0101");
			Symbols_Code_Check.Insert('d', "0100");
			Symbols_Code_Check.Insert('e', "0011");
			Symbols_Code_Check.Insert(',', "0010");
			Symbols_Code_Check.Insert('w', "0001");
			Symbols_Code_Check.Insert('r', "0000");

			char keys[] = { 'l', 'o', ' ', '!' , 'H', 'd', 'e', ',', 'w', 'r' };

			Assert::AreEqual(Memory_Size_Before, (unsigned)104);
			Assert::AreEqual(Memory_Size_After, (unsigned)42);
			for (int i = 0; i < 10; ++i)
				Assert::AreEqual(Symbols_Code[keys[i]], Symbols_Code_Check[keys[i]]);

			delete[] A;
			delete[] B;
		}

		TEST_METHOD(Encode_Decode)
		{
			string str = "Hello, world!";

			unsigned Memory_Size_Before = str.length() * 8, Memory_Size_After = 0;

			RB_TREE_Node<char, unsigned> Frequency;
			Frequency.NIL_N_Root();

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

			unsigned Array_Size = Frequency.Get_Size();

			unsigned* A = new unsigned[Array_Size];
			char* B = new char[Array_Size];

			Frequency.Fill_Array(Frequency.Get_Root(), A, "data");
			Frequency.Fill_Array(Frequency.Get_Root(), B, "key");

			Bubble_Sort(A, B, Array_Size);

			string zero = "";

			RB_TREE_Node<char, string> Symbols_Code;
			Symbols_Code.NIL_N_Root();

			Shannon_Fano(A, B, zero, zero, 0, Array_Size - 1, &Symbols_Code, Memory_Size_After);

			RB_TREE_Node<char, string> Symbols_Code_Check;
			Symbols_Code_Check.NIL_N_Root();
			Symbols_Code_Check.Insert('l', "11");
			Symbols_Code_Check.Insert('o', "101");
			Symbols_Code_Check.Insert(' ', "100");
			Symbols_Code_Check.Insert('!', "011");
			Symbols_Code_Check.Insert('H', "0101");
			Symbols_Code_Check.Insert('d', "0100");
			Symbols_Code_Check.Insert('e', "0011");
			Symbols_Code_Check.Insert(',', "0010");
			Symbols_Code_Check.Insert('w', "0001");
			Symbols_Code_Check.Insert('r', "0000");

			char keys[] = { 'l', 'o', ' ', '!' , 'H', 'd', 'e', ',', 'w', 'r' };

			Assert::AreEqual(Memory_Size_Before, (unsigned)104);
			Assert::AreEqual(Memory_Size_After, (unsigned)42);
			for (int i = 0; i < 10; ++i)
				Assert::AreEqual(Symbols_Code[keys[i]], Symbols_Code_Check[keys[i]]);

			int compression_ratio = round((1 - ((double)Memory_Size_After / (double)Memory_Size_Before)) * 100);
			Assert::AreEqual(compression_ratio, 60);

			string Encoding_Result = "";
			string Encoding_Result_Test = "0101 0011 11 11 101 0010 100 0001 101 0000 11 0100 011 ";
			for (int i = 0; i < str.length(); i++)
			{
				Encoding_Result += Symbols_Code[str[i]] + " ";
			}
			Assert::AreEqual(Encoding_Result, Encoding_Result_Test);

			RB_TREE_Node<string, char> Codes_Symbol;
			Codes_Symbol.NIL_N_Root();
			for (int i = 0; i < Array_Size; ++i)
			{
				Codes_Symbol.Insert(Symbols_Code[B[i]], B[i]);
			}

			string Decoding_Result = "", Code;
			string Decoding_Result_Test = "Hello, world!";
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
			Assert::AreEqual(Decoding_Result, Decoding_Result_Test);

			delete[] A;
			delete[] B;
		}
	};
}

#include "DebugManager.h"
#include <Windows.h>
#include <iostream>

DebugManager::DebugManager()
{
}

void DebugManager::SetColour(unsigned short colour)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
}

void DebugManager::ErrorLog()
{
//***************************************************************************
//					SDL Error Trapping
//***************************************************************************

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		SetColour(12);
		std::cout << "Could not init SDL!" << std::endl;
		SetColour(7);
	}
	else
	{
		SetColour(10);
		std::cout << "SDL is working properly!" << std::endl;
		SetColour(7);
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1)
	{
		SetColour(12);
		std::cout << "Issue initialising VIDEO or EVENTS" << std::endl;
		SetColour(7);
	}
	else
	{
		SetColour(10);
		std::cout << "VIDEO and EVENTS initialised properly" << std::endl;
		SetColour(7);
	}

//***************************************************************************
//					GLEW Error Trapping
//***************************************************************************

	if (glewInit() != GLEW_OK)
	{
		SetColour(12);
		std::cout << "GLEW did not initialize properly" << std::endl;
		SetColour(7);
	}
	else
	{
		SetColour(10);
		std::cout << "GLEW initialized properly!" << std::endl;
		SetColour(7);
	}

	//Check if error occurred and store its value
	GLenum errorValue = glGetError();

	if (errorValue == GL_NO_ERROR)
	{
		SetColour(10);
		std::cout << "No errors!" << std::endl;
		SetColour(7);
		std::cout << "------------------------------------------------" << std::endl;
	}
	else
	{
		SetColour(14);
		std::cout << "Uh oh!" << std::endl;
		SetColour(7);
		std::cout << "------------------------------------------------" << std::endl;
	}
}

void DebugManager::ShaderProgramError()
{
	SetColour(12);
	std::cout << "Error with the shader program" << std::endl;
	SetColour(7);
}

void DebugManager::ShaderCreationError()
{
	SetColour(12);
	std::cout << "Error with the shader creation" << std::endl;
	SetColour(7);
}

//*********************************************************************************************************************************

void DebugManager::CutString(std::string & Str, unsigned int Start, unsigned int Length)
{
	Str = Str.substr(Start, Length);
}

void DebugManager::AddString(std::string & Str, std::string & AddedStr)
{
	Str += " " + AddedStr;
}

void DebugManager::ListString(const std::string & Str)
{
	for (auto it = Str.begin(); it != Str.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	for (size_t i = 0; i < Str.size(); i++)
	{
		std::cout << Str[i] << std::endl;
	}
}

bool DebugManager::SortDescending(int left, int right)
{
	return left > right;
}

bool DebugManager::IsOdd(const int num)
{
	if (num % 2 == 1)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool DebugManager::SortNameLength(std::string Str1, std::string Str2)
{
	if (Str1.size() > Str2.size())
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool DebugManager::SortNameVowel(std::string Str1, std::string Str2)
{
	if (Str1[0] == 'A' || Str1[0] == 'E' || Str1[0] == 'I' || Str1[0] == 'O' || Str1[0] == 'U' ||
		Str1[0] == 'a' || Str1[0] == 'e' || Str1[0] == 'i' || Str1[0] == 'o' || Str1[0] == 'u')
	{
		return true;
	}

	else
	{
		return false;
	}
}

void DebugManager::ParseString(std::string StrParse, std::vector<std::string>& StrVector, std::string Separator)
{
	size_t StrPos = 0;
	std::string SubStr;

	if (StrParse.find(Separator) == std::string::npos)
	{
		SetColour(10);
		std::cout << "Cannot find token separator!" << std::endl;
		SetColour(7);
	}

	while ((StrPos = StrParse.find(Separator)) != std::string::npos)
	{
		SubStr = StrParse.substr(0, StrPos);
		StrVector.push_back(SubStr);
		StrParse.erase(0, StrPos + 1);
		std::cout << SubStr << std::endl;
	}

	if (StrParse.size() > 0)
	{
		StrVector.push_back(StrParse);

		std::cout << StrParse << std::endl;
	}
}

void DebugManager::BinaryToDecimalTable(std::vector<int>& BinaryVector, const int bitrate)
{
	int DecimalNumber = 0;

	std::cout << "Binary = ";

	for (size_t i = 0; i < BinaryVector.size(); i++)
	{
		DecimalNumber += BinaryVector[i] * std::pow(2, (bitrate - 1) - i);

		std::cout << BinaryVector[i];
	}
	std::cout << std::endl;
	std::cout << "Decimal = " << DecimalNumber << std::endl;
}

void DebugManager::DecimalToBinaryDoubling(int DecimalNumber, const int bitrate, std::vector<int>& Binary)
{
	int BinaryNumber = 0;
	int HalvedNumber = 0;

	std::cout << "Decimal = " << DecimalNumber;

	for (size_t i = 0; i < 0; i++)
	{
		HalvedNumber = DecimalNumber / 2;

		if (HalvedNumber % 2)
		{
			Binary.push_back(0);
		}
		else
		{
			Binary.push_back(1);
		}
	}

	std::cout << std::endl;
	std::cout << "Binary = " << std::endl;

	for (size_t i = 0; i < Binary.size(); i++)
	{
		std::cout << Binary[i];
	}
}
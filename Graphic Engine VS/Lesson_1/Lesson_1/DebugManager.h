#ifndef DEBUGMANAGER_H
#define DEBUGMANAGER_H

#include "Singleton.h"
#include <SDL.h>
#include <glew.h>
#include <string>
#include <vector>

class DebugManager
{

public:

	friend class Singleton<DebugManager>;

public:

	DebugManager();

public:

	void SetColour(unsigned short colour);
	void ErrorLog();
	void ShaderProgramError();
	void ShaderCreationError();

//###################################################################################################################
//######################################	-----	TOOLS.H FUNCTIONS	-----	#####################################
public:

	void CutString(std::string& Str, unsigned int Start, unsigned int Length);
	void AddString(std::string& Str, std::string& AddedStr);
	void ListString(const std::string& Str);
	bool SortDescending(int left, int right); //Predicate function that returns true or false (always)
	bool IsOdd(const int num);
	bool SortNameLength(std::string Str1, std::string Str2);
	bool SortNameVowel(std::string Str1, std::string Str2);
	void ParseString(std::string StrParse, std::vector<std::string>& StrVector, std::string Separator);
	void BinaryToDecimalTable(std::vector<int>& BinaryVector, const int bitrate);
	void DecimalToBinaryDoubling(int DecimalNumber, const int bitrate, std::vector<int>& Binary);

};

typedef Singleton<DebugManager> TheDebug;

#endif
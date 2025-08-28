#pragma once
#include <string>
#include "Token.h"
#include "RegexError.h"

class Regex {
public:
	Regex(std::string regularExpression);
	void PrintTokens();
private:
	int currentIndex;
	char curCh;
	std::string regex;
	const int unicodeEscapeDigits = 4;

	std::vector<Token> tokens;
	std::wstring accumilatedStr;
	bool insideEscapeSequence;
	bool insideUnicodeEscape;
	int remainingUnicodeDigits;
	std::string unicodeStr;

	void ParseCharacter();
	void AddToken(Identifier identifier, const DataType& data = std::nullopt);
	void EndCharSequence();
	void EndSequenceAndAddToken(Identifier identifier, const DataType& data = std::nullopt);
	void HandleEscapeSequence();
	void HandleUnicodeEscapeCharacter();
	void AddError(RegexErrorType error);
	void ThrowIfErrors();
};
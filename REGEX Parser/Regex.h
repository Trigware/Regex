#pragma once
#include <string>
#include "Token.h"
#include "RegexError.h"
#include "AST.h"

class Regex {
public:
	Regex(std::string regularExpression);
	void PrintTokens();
	void PrintAST();
private:
	int currentIndex;
	char curCh;
	std::string regex;
	const int unicodeEscapeDigits = 4;

	std::vector<Token> tokens;

	AST ASTree;
	std::vector<Token> GroupedTokens;
	std::wstring accumilatedStr;
	bool insideEscapeSequence;
	bool insideUnicodeEscape;
	int remainingUnicodeDigits;
	std::string unicodeStr;
	Identifier previousIdentifier;
	bool insideOfConcatenationGroup;

	void ParseCharacter();
	void AddToken(Identifier identifier, const DataType& data = std::nullopt);
	void EndCharSequence();
	void EndSequenceAndAddToken(Identifier identifier, const DataType& data = std::nullopt);
	void HandleEscapeSequence();
	void HandleUnicodeEscapeCharacter();
	void AddError(RegexErrorType error);
	void ThrowIfErrors();

	void ConvertTokensToAST();
	void ParseToken(Token token);
	void EndGroupedTokens();
	void StartConcatenationGroup();
	void EndConcatenationGroup();
	void ParseGroupedToken(ASTNode*& groupParent, Token token);
};
#pragma once
#include <string>
#include <optional>
#include <variant>
#include <vector>
#include <iostream>

enum class Identifier {
	CharacterSequence,
	Alteration,
	Wildcard,
	LeftParathesis,
	RightParethesis
};

using DataType = std::optional<std::variant<std::string>>;

class Token {
public:
	Token(Identifier identifer, const DataType& data = std::nullopt);
private:
	Identifier identifier;
	DataType data;
	std::string IdentifierAsString();
	friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

class Regex {
public:
	Regex(std::string regularExpression);
	void PrintTokens();
private:
	int currentIndex;
	std::string regex;
	std::vector<Token> tokens;
	void ParseCharacter();
	void AddToken(Identifier identifier, const DataType& data = std::nullopt);
};
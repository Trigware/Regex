#pragma once
#include <optional>
#include <variant>
#include <vector>
#include <iostream>

enum class Identifier {
	ASTRoot,
	CharacterSequence,
	Alteration,
	Wildcard,
	LeftParathesis,
	RightParethesis,
	TokenGroup
};

using StringType = std::wstring;

using DataType = std::optional<std::variant<StringType>>;

class Token {
public:
	Token(Identifier identifer, const DataType& data = std::nullopt);
	StringType IdentifierAsString();
	StringType GetTokenAsString();
private:
	Identifier identifier;
	DataType data;
};

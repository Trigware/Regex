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
	Concatenation,
	ConcatStart,
	ConcatEnd,
	None
};

using StringType = std::wstring;

using DataType = std::optional<std::variant<StringType>>;

class Token {
public:
	Token(Identifier identifer, const DataType& data = std::nullopt);
	StringType IdentifierAsString();
	StringType GetTokenAsString();
	Identifier GetIdentifier() const { return identifier; }
private:
	Identifier identifier;
	DataType data;
};

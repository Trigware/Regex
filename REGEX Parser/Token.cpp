#include "Token.h"

Token::Token(Identifier id, const DataType& info) {
	identifier = id;
	data = info;
}

StringType Token::IdentifierAsString() {
	switch (identifier) {
		case Identifier::CharacterSequence: return L"Character Sequence";
		case Identifier::Alteration: return L"Alteration";
		case Identifier::Wildcard: return L"Wildcard";
		case Identifier::LeftParathesis: return L"Left Parenthesis";
		case Identifier::RightParethesis: return L"Right Parenthesis";
		case Identifier::ASTRoot: return L"AST Root";
		case Identifier::TokenGroup: return L"Token Group";
	}
	return L"Unknown";
}

StringType Token::GetTokenAsString() {
	StringType result = IdentifierAsString();
	if (data.has_value()) {
		result += L" -> ";
		auto& value = data.value();
		if (std::holds_alternative<StringType>(value)) result += L"(string) " + std::get<StringType>(value);
	}
	return result;
}
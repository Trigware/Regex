#include "Regex.h"

Token::Token(Identifier id, const DataType& info) {
	identifier = id;
	data = info;
}

std::string Token::IdentifierAsString() {
	switch (identifier) {
		case Identifier::CharacterSequence: return "Character Sequence";
		case Identifier::Alteration: return "Alteration";
		case Identifier::Wildcard: return "Wildcard";
		case Identifier::LeftParathesis: return "Left Parenthesis";
		case Identifier::RightParethesis: return "Right Parenthesis";
	}
	return "Unknown";
}

Regex::Regex(std::string regularExpression) {
	regex = regularExpression;
	for (currentIndex = 0; currentIndex < regex.length(); currentIndex++) {
		ParseCharacter();
	}
}

void Regex::ParseCharacter() {
	char ch = regex[currentIndex];
	AddToken(Identifier::CharacterSequence, "TEST");
}

void Regex::AddToken(Identifier identifier, const DataType& data) {
	tokens.emplace_back(identifier, data);
}

void Regex::PrintTokens() {
	for (Token token : tokens) {

	}
}
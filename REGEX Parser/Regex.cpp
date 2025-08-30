#include "Regex.h"
#include "HelperFunctions.h"

Regex::Regex(std::string regularExpression) {
	regex = regularExpression;
	accumilatedStr = L"";
	for (currentIndex = 0; currentIndex < regex.length(); currentIndex++) {
		ParseCharacter();
	}
	EndCharSequence();
	if (insideEscapeSequence) AddError(RegexErrorType::EscapeAtEnd);
	if (insideUnicodeEscape) AddError(RegexErrorType::UnicodeEscapeTooShort);
	ThrowIfErrors();
	ConvertTokensToAST();
}

void Regex::AddToken(Identifier identifier, const DataType& data) {
	tokens.emplace_back(identifier, data);
}

void Regex::PrintTokens() {
	for (Token token : tokens) {
		std::wcout << token.GetTokenAsString() << std::endl;
	}
	std::cout << std::endl;
}

void Regex::PrintAST() {
	ASTree.PrintTree();
}

void Regex::EndCharSequence() {
	if (accumilatedStr == L"") return;
	AddToken(Identifier::CharacterSequence, accumilatedStr);
	accumilatedStr = L"";
}

void Regex::EndSequenceAndAddToken(Identifier identifier, const DataType& data) {
	EndCharSequence();
	AddToken(identifier, data);
}

void Regex::ParseCharacter() {
	curCh = regex[currentIndex];

	if (insideUnicodeEscape) {
		HandleUnicodeEscapeCharacter();
		return;
	}

	if (insideEscapeSequence) {
		HandleEscapeSequence();
		return;
	}

	switch (curCh) {
		case '|': EndSequenceAndAddToken(Identifier::Alteration); break;
		case '.': EndSequenceAndAddToken(Identifier::Wildcard); break;
		case '(': EndSequenceAndAddToken(Identifier::LeftParathesis); break;
		case ')': EndSequenceAndAddToken(Identifier::RightParethesis); break;
		case '\\': insideEscapeSequence = true; break;
		default: accumilatedStr += curCh; break;
	}
}

void Regex::HandleEscapeSequence() {
	insideEscapeSequence = false;
	switch (curCh) {
		case '|': case '.': case '(': case ')': case '\\': accumilatedStr += curCh; return;

		case 'a': accumilatedStr += '\a'; return;
		case 'e': accumilatedStr += '\x1B'; return;
		case 'f': accumilatedStr += '\f'; return;
		case 'n': accumilatedStr += '\n'; return;
		case 'r': accumilatedStr += '\r'; return;
		case 't': accumilatedStr += '\t'; return;
		case 'v': accumilatedStr += '\v'; return;

		case 'u':
			remainingUnicodeDigits = unicodeEscapeDigits;
			insideUnicodeEscape = true;
			unicodeStr = "";
			return;

		default: AddError(RegexErrorType::InvalidEscape);
	}
}

void Regex::HandleUnicodeEscapeCharacter() {
	remainingUnicodeDigits--;
	unicodeStr += curCh;
	if (remainingUnicodeDigits > 0) return;
	insideUnicodeEscape = false;
	try {
		int unicodeValue = Helpers::ConvertFromHex(unicodeStr);
		accumilatedStr += static_cast<wchar_t>(unicodeValue);
	} catch (...) {
		AddError(RegexErrorType::UnicodeNumberInvalid);
	}
}

void Regex::AddError(RegexErrorType error) {
	RegexError::errorList.push_back(error);
}

void Regex::ThrowIfErrors() {
	if (RegexError::errorList.size() == 0) return;
	RegexError err(true);
}
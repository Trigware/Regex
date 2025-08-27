#include "RegexError.h"

RegexError::RegexError(const RegexErrorType& error) {
	regexError = error;
	throw std::exception(what());
}

const char* RegexError::what() const noexcept {
	switch (regexError) {
		case RegexErrorType::InvalidEscape: return "Encountered an invalid escape sequence!";
		case RegexErrorType::EscapeAtEnd: return "Encountered trailing backslash at the end of the regex!";
		case RegexErrorType::UnicodeEscapeTooShort: return "Unicode escape ended prematurely!";
		case RegexErrorType::UnicodeNumberInvalid: return "Number in unicode escape is invalid!";
	}
	return "Unknown Error";
}
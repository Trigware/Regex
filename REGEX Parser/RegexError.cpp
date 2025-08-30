#include "RegexError.h"

std::vector<RegexErrorType> RegexError::errorList = {};

RegexError::RegexError(bool error) {
	throw std::exception(what());
}

const char* RegexError::what() const noexcept {
	int amountOfErrors = errorList.size();
	if (amountOfErrors == 0) return "";
	static std::string result = "Errors (" + std::to_string(amountOfErrors) + "): ";
	for (RegexErrorType error : errorList) {
		result += GetErrorMessage(error) + "\n";
	}
	return result.c_str();
}
 std::string RegexError::GetErrorMessage(RegexErrorType error) {
	switch (error) {
		case RegexErrorType::InvalidEscape: return "Encountered an invalid escape sequence!";
		case RegexErrorType::EscapeAtEnd: return "Encountered trailing backslashs at the end of the regex!";
		case RegexErrorType::UnicodeEscapeTooShort: return "Unicode escape ended prematurely!";
		case RegexErrorType::UnicodeNumberInvalid: return "Number in unicode escape is invalid!";
	}
	return "Unknown Error";
}
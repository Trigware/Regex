#pragma once
#include <exception>
#include <string>
#include <vector>
#include <algorithm>

enum class RegexErrorType {
	InvalidEscape,
	EscapeAtEnd,
	UnicodeEscapeTooShort,
	UnicodeNumberInvalid
};

class RegexError : public std::exception {
public:
	RegexError(bool error);
	static std::vector<RegexErrorType> errorList;
	std::vector<RegexErrorType> code() const {
		return std::vector<RegexErrorType>(errorList);
	}
	const char* what() const noexcept override;
	static std::string GetErrorMessage(RegexErrorType error);
};
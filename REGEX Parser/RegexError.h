#pragma once
#include <exception>

enum class RegexErrorType {
	InvalidEscape,
	EscapeAtEnd,
	UnicodeEscapeTooShort,
	UnicodeNumberInvalid
};

class RegexError : public std::exception {
public:
	RegexError(const RegexErrorType& error);
	RegexErrorType code() const { return regexError; }
	const char* what() const noexcept override;
private:
	RegexErrorType regexError;
};
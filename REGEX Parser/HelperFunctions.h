#pragma once
#include <string>

class Helpers {
public:
	static std::string ChangeToUpper(const std::string& str) { return ChangeCase(str, true); };
	static std::string ChangeToLower(const std::string& str) { return ChangeCase(str, false); };
	static int ConvertToDecimal(std::string value, int fromBase);
	static int ConvertFromHex(std::string hexNumber) { return ConvertToDecimal(hexNumber, 16); };
private:
	static std::string GetDigits(int base);
	static std::string ChangeCase(const std::string& str, bool toUpper);
	static const int caseDifference = 'a' - 'A';
};
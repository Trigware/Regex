#include "HelperFunctions.h"
#include <iostream>
#include <string>

std::string Helpers::ChangeCase(const std::string& str, bool toUpper) {
	std::string result = "";
	char lowerBound = toUpper ? 'a' : 'A';
	char upperBound = toUpper ? 'z' : 'Z';
	int usedDiff = toUpper ? -caseDifference : caseDifference;

	for (char ch : str) {
		if (ch >= lowerBound && ch <= upperBound) ch += usedDiff;
		result += ch;
	}
	return result;
}

int Helpers::ConvertToDecimal(std::string value, int fromBase) {
	std::string digits = GetDigits(fromBase);
	value = ChangeToUpper(value);
	int result = 0;
	int numberOfDigits = value.length();
	for (int i = 0; i < numberOfDigits; i++) {
		char numeral = value[i];
		int numeralValue = digits.find(numeral);
		if (numeralValue == std::string::npos)
			throw std::exception("Invalid numeral for the given base!");
		int power = numberOfDigits - i - 1;
		result += numeralValue * pow(fromBase, power);
	}
	return result;
}

std::string Helpers::GetDigits(int base) {
	std::string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (base < 2 || base > digits.length()) throw std::invalid_argument("Invalid numerical base!");
	return digits.substr(0, base);
}
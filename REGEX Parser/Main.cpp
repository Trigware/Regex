#include <iostream>
#include <regex>
#include "Regex.h"
#include "HelperFunctions.h"

const std::string red = "\033[31m", reset = "\033[0m";

int main() {
	try {
		std::string exampleRegex = R"(\c\)";
		Regex regexExample(exampleRegex);
		regexExample.PrintTokens();

		std::cout << "Give a regular expression: " << std::endl;
		std::string regexInput; std::cin >> regexInput;
		Regex regexFromUser(regexInput);
		regexFromUser.PrintTokens();
	}
	catch (const std::exception& e) {
		std::cout << red << e.what() << reset << std::endl;
	}
}
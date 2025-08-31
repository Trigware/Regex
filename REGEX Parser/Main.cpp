#include <iostream>
#include <regex>
#include "Regex.h"
#include "HelperFunctions.h"
#include <io.h>
#include <fcntl.h>

const std::string red = "\033[31m", reset = "\033[0m";

int main() {
	_setmode(_fileno(stdout), _O_U16TEXT); // Sets output to support UTF-16
	try {
		std::string exampleRegex = R"(a..b)";
		Regex regexExample(exampleRegex);
		regexExample.PrintAST();
	}
	catch (const std::exception& e) {
		std::cout << red << e.what() << reset << std::endl;
	}
}
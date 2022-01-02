#include "stringfn.h"
#include <vector>
#include <string>

#include <sstream>
using namespace std;

//=========================================String functions =================================/
// Temporarily created to mimic certain functions from Java


/**
 * @brief Checks if one string is located inside of another string at the very front
 * 
 * @param bigString The string to search inside
 * @param smallString The string we are trying to look for
 * @return true If smallString was found inside bigString at the very beginning
 * @return false 
 */
bool StringFn::startsWith(string bigString, string smallString) {
	return bigString.compare(0, smallString.length(), smallString) == 0;
}


vector<string> StringFn::splitString(string line, char symbol) {
	vector<string> segments;	// storing segments within this 
	stringstream sentence(line);	// convert string to stringstream
	string segment;					// storing current phrase that was broken by delimiter

	while(getline(sentence, segment, symbol)) {
		segments.push_back(segment);
	}
	return segments;
}


// removes all whitespace from left of string
string StringFn::ltrim(const string& s) {
	const string WHITESPACE = " \n\r\t\f\v";
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

//removes all whitespace from the right of the string
string StringFn::rtrim(const string& s) {
	const string WHITESPACE = " \n\r\t\f\v";
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

// removes all whitespace surrounding string
string StringFn::trim(const string& s) {
	return rtrim(ltrim(s));
}
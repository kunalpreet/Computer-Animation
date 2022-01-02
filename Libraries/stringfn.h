#ifndef STRING_FN_H
#define STRING_FN_H
#include <vector>
#include <string>

using namespace std;

class StringFn {
public:
	static bool startsWith(string, string);
	static vector<string> splitString(string, char);

	//https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
	static string ltrim(const string&);
	static string rtrim(const string&);
	static string trim(const string&);
};


#endif
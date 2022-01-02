#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <string>
#include <fstream> // file reading
#include "XmlNode.h"
#include <regex>

using namespace std;

class XmlParser {
private: 

// regex expressions here
	static regex DATA;			// catches values between <asdf> datadata </data>
	static regex START_TAG;	// catches start tag of a line <asdf>
	static regex ATTR_NAME;		// catches atribute names, i.e. attr=
	static regex ATTR_VAL;	// catches attribute values, i.e. attr="32"
	static regex CLOSED;		// catches </asdf> ending tags, or the /> of the <asdf />


public:
	static void printNode(XmlNode&);
    static XmlNode loadFromFile(ifstream&);

private:
	static XmlNode loadNode(ifstream&);
	static void addData(string, XmlNode&);
	static void addAttributes(vector<string>, XmlNode&);
	static void addAttribute(string, XmlNode&);
	static string getStartTag(string);
public:
// string functions ; may move them out and into its own library one day
	static bool startsWith(string, string);
	static vector<string> splitString(string, char);

	//https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
	static string ltrim(const string&);
	static string rtrim(const string&);
	static string trim(const string&);


};

#endif
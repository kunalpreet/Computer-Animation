
#include "XmlParser.h"
#include "XmlNode.h"
#include "../../Libraries/stringfn.h"
#include <vector>
#include <string>
#include <algorithm> // replace function for string
#include <fstream> // file reading
#include <iostream>

using namespace std;


/**
 * Note: When matching, we usually get two results. Let's say
 * for example, let's say we use this
19:  <znear sid="znear">0.1</znear>
19:        Matched DATA:  		  [>0.1<][0.1]
19:        Matched START_TAG:     [<znear sid="znear">][znear sid="znear"]
19:        Matched ATTR_NAME:     [            <znear sid=][            <znear sid]
19:        Matched ATTR_VAL:      ["znear"][znear]
19:        Matched CLOSED:        [</][</]
 * note that the second option actively removes  the <> and "" from the first
 * in DATA, START_TAG< and ATTR_VAL? This means we should use the second of the smatch data type.
 * for ATTR_NAME; the first < would be removed when moving between functions anyways
 */

// regex expressions here	
regex XmlParser::DATA(">(.+?)<");			// catches values between <asdf> datadata </data> - removing the > and < from '> ... <' when getting m[1]
regex XmlParser::START_TAG("<(.+?)>");		// catches start tag of a line <asdf> - every line should have this (We are basically removing <> from line when getting m[1])
regex XmlParser::ATTR_NAME("(.+?)=");		// catches atribute names, i.e. attr= - removing the equal signs when getting m[1]
regex XmlParser::ATTR_VAL("\"(.+?)\"");	// catches attribute values, i.e. attr="32" 
regex XmlParser::CLOSED("(<\\/|\\/>)");		// catches </asdf> ending tags, or the /> of the <asdf/>

void XmlParser::printNode(XmlNode & node) {
	cout << node.getName() << " - " << node.getData() << endl; 
	for (auto attrib : node.attributes) {
		cout << "\tAttr:" << attrib.first << " - " << attrib.second << endl;
	}
	for (auto child : node.childNodes) {
		cout << "\t\tChildNode - " << child.first << endl;
		for (auto t : child.second) {
			printNode(t);
		}
	}
}

XmlNode XmlParser::loadFromFile(ifstream& file) {
	// an ifstream already passed from another caller; ifstream already has path
	// if file failed, then we tell them nothing changes
	if (file.fail()) {
		cout << "File path failed - could not load the file from given path." << std::endl;
		exit(0);
		// return XmlNode("");
	}

	// else, we start reading!
	string line = "";
	getline(file, line); // reading version line and skipping


	// passing the filereader to loadNode
	XmlNode node = loadNode(file);
	// node should have everything now...
	// printNode(node);
	file.close();
	return node;
}

// recursive function that is continuously called to go through the XML file and parse them into nodes
XmlNode XmlParser::loadNode(ifstream& file) {

	string line;
	getline(file, line);	// read a line, then trim it
	line =  StringFn::trim(line);
	// if line starts with a </ at the beginning
	if (StringFn::startsWith(line, "</")) {
		return XmlNode("");
	}
	
	// we are in a valid line; start checking stuff
	string startTagLine = getStartTag(line);
	if (startTagLine == "/>No start tag found!!") {
		exit(0);
	}
	vector<string> startTagParts = StringFn::splitString(startTagLine, ' ');
	
	// the first word in this line is the name of this node
	string name(startTagParts.front());
	// just in case the name has a '/' in front, we replace it
	// (char) 0 is the equivalent of '', an empty char. so we replace all '/' with ''
	// instead of (char) 0, we can also use '\0'
	replace(name.begin(), name.end(), '/', (char) 0);
	// make new node for this name
	XmlNode node(name);

	// adding attributes and data to this node
	addAttributes(startTagParts, node);
	addData(line, node);

	// checking it the line we are on is closing
	// if it is, we are done editing this node
	if (regex_search(line, CLOSED)) {
		return node;
	}
	
	// otherwise, we continue and add future nodes as children
	XmlNode child = loadNode(file);
	while (child.getName() != "") {
		node.addChild(child);
		child = loadNode(file); // getting new
	}
	return node;
}

void XmlParser::addData(string line, XmlNode& node) {
	// RegEx doesn't work if line is too long to match...
	// If line is over 6800, things break

	smatch dataMatch;
	if (line.length() < 6800) {
		if (regex_search(line, dataMatch, DATA, regex_constants::match_any)) {
			node.setData(dataMatch[1]);
		}
	} else {
		// the only time we ever end up with a line of length 6800 is... when we have a giant array of floats...
		// <...>....data....<...>
		// So we do it the budget way: Splitting at > and < and then sending it back out...
		string removeLeft = StringFn::splitString(line, '>').at(1); 		// [<...>][....data....<...>]
		string removed = StringFn::splitString(removeLeft, '<').at(0);		// [....data....][<...>]
		node.setData(removed);
	}


}

void XmlParser::addAttributes(vector<string> titleParts, XmlNode& node) {
	for (auto line : titleParts) {
		// if it finds an equal side (i.e. not no position)
		if (line.find("=")  != string::npos) {
			// then this line has an attribute-value!
			addAttribute(line, node);
		}
	}
}

void XmlParser::addAttribute(string attributeLine, XmlNode& node) {
	// need to parse this line with regex for attribute and value, then add to node
	smatch nameMatch, valueMatch; //storing regex matching phrases
	regex_search(attributeLine, nameMatch, ATTR_NAME);
	regex_search(attributeLine, valueMatch, ATTR_VAL);

	// Receiving a line that contains <attribute="value">
	// nameMatch[1] = attribute, valueMatch[1] = value
	node.addAttribute(nameMatch[1], valueMatch[1]);
}

/**
 * @brief When given a line, looks for the starting tag
 * 
 * @param line The line that we are parsing
 * @return string Gives the section of the line that matches the REGEX of a start tag "<(.+?>"
 */
string XmlParser::getStartTag(string line) {
	smatch startMatch; //storing found phrases inside m
	if (regex_search(line, startMatch, START_TAG)) {
		// matching line against the StartTag
		// Matched START_TAG: <znear sid="znear">, znear sid="znear"
		// we want second one
		return startMatch[1];
	}
	return "/>No start tag found!!";
}





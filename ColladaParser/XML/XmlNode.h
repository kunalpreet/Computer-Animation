#ifndef XML_NODE_H
#define XML_NODE_H

#include <vector>
#include <string>
#include <map>


using namespace std;

/**
 * @brief Represents a node in an Xml file. Contains the name, a map of the attributes and their values in the node, any text data, and any children nodes.
 * 
 */
class XmlNode {
private:
    string name;
public:
    map<string, string> attributes;  
    string data;
    map<string, vector<XmlNode>> childNodes;


public:
    XmlNode(string);
    string getName();

    void setData(string);
    string getData();

    void addAttribute(string, string);
    string getAttribute(string);

    void addChild(XmlNode&);
    XmlNode getChild(string);

    XmlNode getChildWithAttribute(string, string, string);

    vector<XmlNode> getChildren(string);
};


#endif
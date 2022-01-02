#include "XmlNode.h"
#include <vector>
#include <string>
#include <map>
#include <utility>


using namespace std;

XmlNode::XmlNode(string name) {
    this->name = name;
}
string XmlNode::getName() {
    return this->name;
}

 void XmlNode::setData(string data) {
    this->data = data;
}

string XmlNode::getData() {
    return this->data;
}

// pushes an attribute and its value to the map
void XmlNode::addAttribute(string attr , string value) {
    auto attribute = make_pair(attr, value);
    this->attributes.insert(attribute);
}

/**
 * @brief checks map to see if it has an attribute, and returns the value
 * 
 * @param attr the attribute to look for in the XmlNode
 * @return string Returns the value of the attribute on success, else returns empty string ""
 */
string XmlNode::getAttribute(string attr) {
    // checking if attr key exists in attributes
    if (this->attributes.count(attr))
        return this->attributes.at(attr);
    
    return string();
}

// Given a XmlNode, we add it as a child to the map with its name as the key
void XmlNode::addChild(XmlNode& child) {
    // Map is <String, Vector> - multiple children with the same name are stored in vector

    // If child node is NOT already in list
    if (!this->childNodes.count(child.name)) {
        // make a new entry with an empty vector as value in key-value pair
        vector<XmlNode> newVec;

        // empty vec paired with child.name
        auto newChild = make_pair(child.name, newVec);
        this->childNodes.insert(newChild);
    }

    // if entry exists, we just add child to the vector in the <string, vector> pair
    this->childNodes[child.name].push_back(child);
}

/**
 * @brief Given a string name, we attempt to find the XmlNode with that name in the children map
 * 
 * @param childName The child XmlNode to look for
 * @return XmlNode Returns the XmlNode with the childName on success; else, returns an XmlNode with an null for its name 
 */
XmlNode XmlNode::getChild(string childName) {
    if(this->childNodes.count(childName)) {
         // returns first element of vector
        return this->childNodes.at(childName).front();
    }
    // no child found
    return XmlNode(string());
}

/**
 * @brief Given strings of name, attribute, and a value we attempt to find the XmlNode with the same parameters in the children map
 * 
 * @param childName Name of XmlNode
 * @param attr Attribute
 * @param value Value of attribute
 * @return XmlNode Returns XmlNode with the same parameters; else returns an empty XmlNode
 */
XmlNode XmlNode::getChildWithAttribute(string childName, string attr, string value) {
    if (this->childNodes.count(childName)) {
        // vector from key-value pair
        auto childList = childNodes.at(childName);

        // go through vector to check their parameters
        for (XmlNode child : childList) {
            // comparing attribute and values
            string val = child.getAttribute(attr);

            // if getAttribute succeeds, return child; else, returns failed XmlNode
            if (val == value) 
                return child;
        }
    }
    
    return XmlNode(string());
}

/**
 * @brief given a child node name, returns the vector of all child nodes with that name
 * 
 * @param name 
 * @return vector<XmlNode> 
 */
vector<XmlNode> XmlNode::getChildren(string name) {
    vector<XmlNode> vec;
    if (this->childNodes.count(name)) {
        return childNodes.at(name);
    }
    return vec;
}
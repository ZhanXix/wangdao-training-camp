/*
使用tinyXml2解析RSS文件，并生成一个网页库pagelib.dat
（教师范例）
*/

#include "tinyxml2.h"
#include <iostream>
#include <regex>
#include <string>
using std::cout;
using std::endl;
using std::string;

using namespace tinyxml2;

void test0()
{
	XMLDocument doc;
	doc.LoadFile("coolshell.xml");
	if (doc.ErrorID()) {
		cout << "XMLDocument load file error!" << endl;
		return;
	}

	XMLElement* itemNode = doc.FirstChildElement("rss")
		->FirstChildElement("channel")
		->FirstChildElement("item");
	
	do {
		XMLElement* titleNode = itemNode->FirstChildElement("title");
		const char* title = titleNode->GetText();
		cout << "title: " << title << endl;

		XMLElement* linkNode = itemNode->FirstChildElement("link");
		const char* link = linkNode->GetText();
		cout << "link: " << link << endl;

		XMLElement* contentNode = itemNode->FirstChildElement("content:encoded");
		const char* content = contentNode->GetText();
		//cout << "content:" << content << endl;

		std::regex re("<.+?>");

		//learning by doing
		string contentProcessed = std::regex_replace(content, re, "");
		cout << "content:" << contentProcessed << endl;

	} while (itemNode->NextSiblingElement("item"));
}


int main()
{
	test0();
	return 0;
}
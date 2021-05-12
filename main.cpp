#include"LexicalAnalyzer.h"
#include<iostream>
#include <fstream>
#include <string>
#include <sstream>
int main() {
	
	string fileName = "data.txt";
	ifstream ifile(fileName);
	//将文件读入到ostringstream对象buf中
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);

	LexicalAnalyzer l(buf.str());
	l.scan();
	for (int i = 0; i < l.tokenList.size(); i++) {
		if (l.tokenList[i].tokenType == keyword) {
			cout<<"KEYWORD "<<l.keywordTable[l.tokenList[i].index]<<endl;
		}
		else if (l.tokenList[i].tokenType == identifier) {
			cout << "IDENGTIFIER " << l.identifierTable[l.tokenList[i].index] << endl;
		}
		else if (l.tokenList[i].tokenType == INT10) {
			cout << "INT10 " <<dec << l.int10Table[l.tokenList[i].index] << endl;
		}
		else if (l.tokenList[i].tokenType == INT8) {
			cout << "INT8 " << oct << l.int8Table[l.tokenList[i].index] << endl;
		}
		else if (l.tokenList[i].tokenType == INT16) {
			cout << "INT16 " << hex << l.int16Table[l.tokenList[i].index] << endl;
		}
		else if (l.tokenList[i].tokenType == operato) {
			cout << "OPERATOR " <<  l.operatorTable[l.tokenList[i].index] << endl;
		}
	}

}
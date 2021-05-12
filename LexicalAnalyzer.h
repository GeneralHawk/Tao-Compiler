#pragma once
#include<vector>
#include<string>
using namespace std;

enum TokenType { keyword, identifier, operato, INT10, INT8, INT16 };
typedef struct Token
{
	TokenType tokenType;
	int index;
}Token;
class LexicalAnalyzer
{
public:
	const vector<string> keywordTable = { "if","then","else","while","do" };
	const vector<string> operatorTable = { "+","-","*","/",">","<","=","(",")",";" };
	vector<int> int10Table;
	vector<int> int8Table;
	vector<int> int16Table;
	vector<string> identifierTable;
	const char endWord = '#';
	int state = 1;
	int index = 0;
	string content;
	char nextToken();
	void readKeywordOrIdentifier(string& currentWord,char& nextChar);
	void readINT10(string& currentWord, char& nextChar);
	void read0OrINT8OrINT16(string& currentWord, char& nextChar);
	void addOperator(char ch,char& nextChar);
	
public:
	LexicalAnalyzer(string content);
	vector<Token> tokenList;
	void scan();


};


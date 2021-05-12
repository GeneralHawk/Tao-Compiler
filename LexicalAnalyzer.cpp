#include "LexicalAnalyzer.h"
#include<fstream>

LexicalAnalyzer::LexicalAnalyzer(string content) {
	this->content = content;
}

char LexicalAnalyzer::nextToken(){
	char ch;
	ch = content[index];
	while (ch==' ' || ch == '\n' || ch == '\t') {
		ch = content[++index];
	}
	return ch;
}

void LexicalAnalyzer::readKeywordOrIdentifier(string& currentWord,char& nextChar){
	char ch = content[++index];
	while ((ch <= 'z' && ch >= 'a')||(ch <= 'Z' && ch >= 'A')||(ch <= '9' && ch >= '0')) {
		currentWord.push_back(ch);
		ch = content[++index];
	}
	nextChar = ch;
	state = 3;
}

void  LexicalAnalyzer::readINT10(string& currentWord, char& nextChar) {
	char ch = content[++index];
	while (ch >= '0' && ch <= '9') {
		currentWord.push_back(ch);
		ch = content[++index];
	}
	nextChar = ch;

}

void LexicalAnalyzer::read0OrINT8OrINT16(string& currentWord, char& nextChar) {
	char ch = content[++index];
	if (ch != 'o' && ch != 'x') {
		state = 7;
		nextChar = ch;
		return;
	}
	if (ch == 'o') {
		state = 8;
		ch = content[++index];
		if (ch < '0' || ch>'7') {//若读到0o后读到的字符不为0-7的数字，则视为读到0，并将索引回退到o，继续进行读取
			state = 7;
			index --;
			nextChar = content[index];
			currentWord = "0";
			return;
		}
		else {
			state = 9;
			currentWord = "";
			currentWord.push_back(ch);
			while (ch <= '7' && ch >= '0') {
				ch = content[++index];
				currentWord.push_back(ch);
			}
			state = 10;
			nextChar = ch;
			return;
		}
	}
	else if (ch == 'x') {
		state = 12;
		ch = content[++index];
		if (ch < '0' || (ch > '9' && ch < 'a') || ch>'f') {//若读到0x后读到的字符不为0-9的数字也不为a-f的字母，则视为读到0，并将索引回退到x，继续进行读取
			state = 7;
			index--;
			nextChar = content[index];
			currentWord = "0";
			return;
		}
		else {
			state = 13;
			currentWord = "";
			currentWord.push_back(ch);
			while ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f')) {
				ch = content[++index];
				currentWord.push_back(ch);
			}
			state = 14;
			nextChar = ch;
			return;
		}
	}
}

void LexicalAnalyzer::addOperator(char ch,char& nextChar) {
	Token token;
	if (ch == '+') {
		token.tokenType = operato;
		token.index = 0;
		tokenList.push_back(token);
		nextChar = content[++index];
	}
	else if (ch == '-') {
		token.tokenType = operato;
		token.index = 1;
		tokenList.push_back(token);
		nextChar = content[++index];
	}
	else if (ch == '*') {
		token.tokenType = operato;
		token.index = 2;
		tokenList.push_back(token);
		nextChar = content[++index];
	}
	else if (ch == '/') {
		token.tokenType = operato;
		token.index = 3;
		tokenList.push_back(token);
		nextChar = content[++index];
	}
	else if (ch == '>') {
		token.tokenType = operato;
		token.index = 4;
		tokenList.push_back(token);
		nextChar = content[++index];
	}
	else if (ch == '<') {
		token.tokenType = operato;
		token.index = 5;
		tokenList.push_back(token);
		nextChar = content[++index];
	}
	else if (ch == '=') {
		token.tokenType = operato;
		token.index = 6;
		tokenList.push_back(token);
		nextChar = content[++index];
	}
	else if (ch == '(') {
		token.tokenType = operato;
		token.index = 7;
		tokenList.push_back(token);
		nextChar = content[++index];
	}
	else if (ch == ')') {
		token.tokenType = operato;
		token.index = 8;
		tokenList.push_back(token);
		nextChar = content[++index];
	}
	else if (ch == ';') {
		token.tokenType = operato;
		token.index = 9;
		tokenList.push_back(token);
		nextChar = content[++index];
	}
}

void LexicalAnalyzer::scan() 
{
	char ch = nextToken();
	while (ch != endWord) {
		char nextChar;
		if (ch <= 'z' && ch >= 'a' || ch <= 'Z' && ch >= 'A') {
			state = 2;
			string currentWord="";
			currentWord.push_back(ch);
			readKeywordOrIdentifier(currentWord, nextChar);
			bool isKeyword = false;
			for (int i = 0; i < keywordTable.size(); i++) {
				if (currentWord == keywordTable[i]) {
					Token token;
					token.tokenType = keyword;
					token.index = i;
					tokenList.push_back(token);
					isKeyword = true;
					break;
				}
			}
			if (!isKeyword) {
				Token token;
				token.tokenType = identifier;
				identifierTable.push_back(currentWord);
				token.index = identifierTable.size() - 1;
				tokenList.push_back(token);
			}
		}
		else if (ch <= '9 ' && ch >= '1') {
			state = 4;
			string currentWord = "";
			currentWord.push_back(ch);
			readINT10(currentWord, nextChar);
			int int10 = atoi(currentWord.c_str());
			Token token;
			int10Table.push_back(int10);
			token.tokenType = INT10;
			token.index = int10Table.size() - 1;
			tokenList.push_back(token);
		}
		else if (ch == '0') {
			state = 6;
			string currentWord = "";
			currentWord.push_back(ch);
			read0OrINT8OrINT16(currentWord, nextChar);
			if(state==7){
				int int10 = atoi(currentWord.c_str());
				Token token;
				int10Table.push_back(int10);
				token.tokenType = INT10;
				token.index = int10Table.size() - 1;
				tokenList.push_back(token);
			}
			else if (state == 10) {
				int int8 = strtol(currentWord.c_str(),NULL,8);
				Token token;
				int8Table.push_back(int8);
				token.tokenType = INT8;
				token.index = int8Table.size() - 1;
				tokenList.push_back(token);
			}
			else if (state == 14) {
				int int16 = strtol(currentWord.c_str(), NULL, 16);
				Token token;
				int16Table.push_back(int16);
				token.tokenType = INT16;
				token.index = int16Table.size() - 1;
				tokenList.push_back(token);
			}
			else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')' || ch == ';') {
				addOperator(ch, nextChar);
			}
			else {
				printf("ERROR");
				break;
			}
			
		}

		ch = nextChar;
		if (ch == ' ' || ch == '\n' || ch == '\t') {
			ch = nextToken();
		}
		state = 1;
		
	}
}
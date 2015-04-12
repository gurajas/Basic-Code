#include "Symbol.h"

#include <string>
#include <vector>
#include <cstdio>

#include "types.h"
#include <iostream>


using namespace std;

Symbol::Symbol() {
	myName = "";
	myLine = 0;
	myReturnType = UNKNOWN_RT;
	mySymbolType = UNKNOWN_ST;
	myOffset = 0;
}

Symbol::~Symbol() {

}

// Set the identifier text
void Symbol::SetName(string name) {
	if (!name.empty()) {
		myName = name;
	}
}

// Get the identifier text
string Symbol::GetName(void) {
	return myName;
}

// Set declaration line
void Symbol::SetLine(int line) {
	myLine = line;
}

// Get declaration line
int Symbol::GetLine() {
	return myLine;
}

// Set return type
void Symbol::SetReturnType(ReturnType type) {
	myReturnType = type;
}

// Get return type
ReturnType Symbol::GetReturnType() {
	return myReturnType;
}

// Set symbol type
void Symbol::SetSymbolType(SymbolType type) {
	mySymbolType = type;
}

// Get symbol type
SymbolType Symbol::GetSymbolType() {
	return mySymbolType;
}

// Get offset (used during code generation)
int Symbol::GetOffset() {
	return myOffset;
}

// Set offset (used during code generation)
void Symbol::SetOffset(int offset) {
	myOffset = offset;
}

// Add a parameter to the end of the parameter list
void Symbol_Subprogram::AddParameter(Symbol *symbol) {
	if (symbol != NULL) {
		parameters.push_back(symbol);
	}
}

Symbol * Symbol_Subprogram::GetParameter(unsigned int num) {
	if (num <= parameters.size()) {
		return parameters[num];
	}
	return NULL;
}

int Symbol_Subprogram::GetParameterCount() {
	return parameters.size();
}

Symbol_Subprogram::~Symbol_Subprogram() {
	parameters.clear();
}

void Symbol_Subprogram::Dump(FILE * file, int indent) {
	if (file == stdout) {

		for (int i = 0; i < indent; i++) {
			//file << " ";
			//fwrite(" ", sizeof(" "), sizeof(" "), file);
			cout << " ";
		}
		for (vector<Symbol *>::iterator it = parameters.begin();
				it != parameters.end(); it++) {
			//file << ReturnTypeToString((*it)->GetReturnType());
			cout << ReturnTypeToString((*it)->GetReturnType());
			//fwrite(ReturnTypeToString((*it)->GetReturnType()),
			//			sizeof(ReturnTypeToString((*it)->GetReturnType())),
			//		sizeof(ReturnTypeToString((*it)->GetReturnType())), file);
			//file << (*it)->GetName();
			cout << (*it)->GetName();
			//file << SymbolTypeToString((*it)->GetSymbolType());
			cout << SymbolTypeToString((*it)->GetSymbolType());
		}
	}
}

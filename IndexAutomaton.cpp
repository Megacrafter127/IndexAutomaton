/*
 * automaton.cpp
 *
 *  Created on: 19.01.2016
 *      Author: Megacrafter127
 */

#include "IndexAutomaton.hpp"
#include <cstring>
#include <iostream>

using namespace std;

IndexAutomaton::sf::sf(const size_t next[255], const bool end) {
	this->end=end;
	for(unsigned char i=0;i<255;i++) this->next[i]=next[i];
}

IndexAutomaton::sf::sf(const bool end) {
	this->end=end;
	for(unsigned char i=0;i<255;i++) this->next[i]=0;
}

size_t &IndexAutomaton::sf::operator[](unsigned char idx) {
	return this->next[idx];
}

bool IndexAutomaton::sf::operator!() {
	return !this->end;
}

IndexAutomaton::sf::operator bool() {
	return this->end;
}

IndexAutomaton::~IndexAutomaton() {
	free(this->searchString);
	free(this->stateFunc);
}

IndexAutomaton::IndexAutomaton(const char *searchString) {
	this->currentState=0;
	this->inputCount=0;
	this->stateCount=strlen(searchString)+1;
	this->searchString=new char[this->stateCount];
	strcpy(this->searchString,searchString);
	this->stateFunc=new struct sf[this->stateCount];
	for(size_t i=0;i<this->stateCount;i++) {
		unsigned char c=searchString[i]-1;
		if(c<255) this->stateFunc[i][c]=i+1;
		for(size_t j=0;j<1+i/2;j++) {
			bool match=true;
			for(size_t k=j;k<i;k++) {
				if(searchString[k]!=searchString[k-j]) {
					match=false;
					break;
				}
			}
			if(match && searchString[i]!=searchString[j]) {
				this->stateFunc[i][static_cast<unsigned char>(searchString[j])-1]=j+1;
			}
		}
	}
	this->stateFunc[this->stateCount-1].end=true;
}

IndexAutomaton::IndexAutomaton(const IndexAutomaton &src) {
	this->currentState=0;
	this->stateCount=src.stateCount;
	this->stateFunc=new struct sf[this->stateCount];
	for(size_t i=0;i<this->stateCount;i++) {
		this->stateFunc[i]=src.stateFunc[i];
	}
	this->inputCount=0;
	this->searchString=new char[this->stateCount];
	strcpy(this->searchString,src.searchString);
}

IndexAutomaton &IndexAutomaton::parse(const char character) {
	this->currentState=this->stateFunc[this->currentState][static_cast<unsigned char>(character)-1];
	this->inputCount++;
	if(this->stateFunc[this->currentState]) {
		this->matches.insert(this->inputCount+1-this->stateCount);
	}
	return *this;
}

IndexAutomaton &IndexAutomaton::parse(const char *string) {
	if(string) for(size_t i=0;string[i];i++) {
		parse(string[i]);
	}
	return *this;
}

IndexAutomaton &IndexAutomaton::operator<<(const char *string) {
	return parse(string);
}

IndexAutomaton::iterator IndexAutomaton::begin() {
	return this->matches.begin();
}
IndexAutomaton::iterator IndexAutomaton::end() {
	return this->matches.end();
}

IndexAutomaton::reverse_iterator IndexAutomaton::rbegin() {
	return this->matches.rbegin();
}
IndexAutomaton::reverse_iterator IndexAutomaton::rend() {
	return this->matches.rend();
}

bool IndexAutomaton::hasMatch() {
	return !!*this;
}

IndexAutomaton::operator bool() {
	return hasMatch();
}

bool IndexAutomaton::operator!() {
	return this->matches.empty();
}

bool IndexAutomaton::hasEndMatch() {
	return this->stateFunc[this->currentState];
}

bool IndexAutomaton::operator~() {
	return hasEndMatch();
}

size_t IndexAutomaton::getMatchCount() {
	return this->matches.size();
}
IndexAutomaton::operator size_t() {
	return getMatchCount(); 
}

IndexAutomaton &IndexAutomaton::reset() {
	this->currentState=0;
	this->matches.clear();
	this->inputCount=0;
	return *this;
}

IndexAutomaton &IndexAutomaton::operator--() {
	return reset();
}

ostream &IndexAutomaton::print(ostream &stream) {
	for(size_t i=0;i<this->stateCount;i++) {
		stream << i;
		if(i>0) {
			stream.put('(');
			stream.put(this->searchString[i-1]);
			stream.put(')');
		} else stream << "   ";
		stream << ": ";
		if(this->stateFunc[i]) stream << "! ";
		for(unsigned char c=0;c<255;c++) {
			size_t n=this->stateFunc[i][c];
			if(n) {
				(stream << "( ").put(static_cast<char>(c+1)) << " , " << n << " ) ";
			}
		}
		stream << endl;
	}
	return stream;
}

/*
 * test.cpp
 *
 *  Created on: 15.10.2016
 *      Author: Megacrafter127
 */

#ifdef DEBUG
#include "IndexAutomaton.hpp"
#include <iostream>

using namespace std;

int main(int vc,char** va) {
	vc--;
	if(vc) {
		IndexAutomaton a(va[1]);
		if(vc==1) a.print(cout);
		else {
			bool need=false;
			for(int i=1;i<vc;i++,--a) {
				a << va[i+1];
				if(!a) cout << i << ": No matches" << endl;
				else for(auto &&matchIdx:a) {
					if(need) cout << endl;
					else need=true;
					cout << i << ": " << matchIdx;
				} if(~a) {
					cout << " end";
				}
				cout << endl;
				if(i<vc-1) cout << endl;
			}
		}
	} else {
		cout << "Usage: [pattern] [inputs]*" << endl;
		cout << "If there are no inputs, prints the automaton, otherwise prints all matches and their indizes." << endl;
	}
	return 0;
}
#endif

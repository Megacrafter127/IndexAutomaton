/*
 * IndexAutomaton.h
 *
 * Created on: 19.01.2016
 * Author: Megacrafter127
 */

#ifndef INDEX_AUTOMATON_H_
#define INDEX_AUTOMATON_H_

#include <set>
#include <ostream>

namespace std {
	
	class IndexAutomaton {
	public:
		struct sf {
			bool end;
			std::size_t next[255];
			sf(const std::size_t next[255], const bool end=false);
			sf(const bool end=false);
			std::size_t &operator[](unsigned char);
			bool operator!();
			operator bool();
		};
	protected:
		std::size_t currentState,stateCount;
		struct sf *stateFunc;
		std::set<std::size_t> matches;
		std::size_t inputCount;
		char *searchString;
		
	public:
		typedef std::set<std::size_t>::iterator iterator;
		typedef std::set<std::size_t>::reverse_iterator reverse_iterator;
		
		~IndexAutomaton();
		IndexAutomaton(const char *searchString="\0");
		IndexAutomaton(const IndexAutomaton &src);
		
		IndexAutomaton &parse(const char character);
		
		IndexAutomaton &parse(const char *string);
		IndexAutomaton &operator<<(const char *string);
		
		iterator begin();
		iterator end();
		
		reverse_iterator rbegin();
		reverse_iterator rend();
		
		bool hasMatch();
		operator bool();
		bool operator!();
		
		bool hasEndMatch();
		bool operator~();
		
		std::size_t getMatchCount();
		operator std::size_t();
		
		IndexAutomaton &reset();
		IndexAutomaton &operator--();
		
		std::ostream &print(std::ostream &stream);
	};
}
#endif /* INDEX_AUTOMATON_H_ */

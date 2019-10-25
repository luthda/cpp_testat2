#include "Word.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

Word::Word(string word)
	: word{word} {
		if (!isValidWord(word)) {
			throw invalid_argument("this is not a word!!!!!");
		}
}

bool Word::isValidWord(string word) const {
	if (word.empty()) {
		return false;
	}
	all_of(cbegin(word), cend(word), [] (auto const character) {
		return isalpha(character);
	});
	return false;
}

void Word::removeNotAlpha(istream &in) {
	while(!isalpha(in.peek())) {
		in.get();
	}
}

void Word::writeWord(istream &in) {
	string writeString{ };
	while (isalpha(in.peek()) != 0) {
		writeString.push_back(in.get());
	}
	word = writeString;
}

istream &Word::read(istream &in) {
	if (!in.eof()) {
		removeNotAlpha(in);
		writeWord(in);
	}
	return in;
}

ostream &Word::print(ostream &out) const {
	out << word;
	return out;
}



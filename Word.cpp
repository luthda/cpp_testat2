#include "Word.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
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
	bool valid{ };
	valid = all_of(begin(word), end(word), [] (auto const character) {
		return isalpha(character);
	});
	return valid;
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

bool Word::operator<(Word const &rhs) const {
	return lexicographical_compare(begin(word), end(word), begin(rhs.word), end(rhs.word), [] (char leftChar, char rightChar) {
		return tolower(leftChar) < tolower(rightChar);
	});
}

bool Word::operator==(Word const &rhs) const {
	return equal(begin(word), end(word), begin(rhs.word), end(rhs.word), [] (char leftChar, char rightChar) {
		return tolower(leftChar) == tolower(rightChar);
	});
}



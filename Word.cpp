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

bool Word::isValidWord(string word) {
	bool isValid{true};
	for_each(cbegin(word), cend(word), [&isValid] (auto const character) {
		if (!isalpha(character)) {
			isValid = false;
			return isValid;
		}
	});
	return isValid;
}

bool Word::hasStillValidChar(istream &in) {
	bool hasValidChar{false};
	while (!in.eof()) {
		if (isalpha(in.peek())) {
			hasValidChar = true;
		}
	}
	return hasValidChar;
}

void Word::removeNotAlpha(istream &in) {
	while(!in.eof()) {
		if (!isalpha(in.peek())) {
			in.get();
		}
		else {
			break;
		}
	}
}

void Word::writeWord(istream &in) {
	while (!in.eof()) {
		if (isalpha(in.peek())) {
			word.push_back(in.get());
		}
	}
}

istream &Word::read(istream &in) {
	bool hasValidChars{false};
	while (!in.eof()) {
		hasValidChars = hasStillValidChar(in);
		if (hasValidChars) {
			word.clear();
			removeNotAlpha(in);
			writeWord(in);
		}
	}
	return in;
}


ostream &Word::print(ostream &out) const {
	out << word;
	return out;
}



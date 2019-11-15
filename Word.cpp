#include "word.h"

#include <algorithm>
#include <iterator>
#include <stdexcept>

namespace text{

	using namespace std;

	bool isValidWord(string word) const {
		if (word.empty()) {
			return false;
		}
		return all_of(begin(word), end(word), [] (auto const character) {
			return isalpha(character);
		});
	}

	Word::Word(string word)
		: word{word} {
			if (!isValidWord(word)) {
				throw invalid_argument{"this is not a word!!!!!"};
			}
	}

	void removeNotAlpha(istream &in) {
		while(in.good() && !isalpha(in.peek())) {
			in.ignore();
		}
	}

	string  readWord(istream &in) {
		string writeString{ };
		while (isalpha(in.peek())) {
			writeString.push_back(in.get());
		}
		return writeString;

	}

	istream &Word::read(istream &in) {
		removeNotAlpha(in);
		string newWord = readWord(in);
		if (isValidWord(newWord)) {
			word = newWord;
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
}


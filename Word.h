#ifndef WORD_H_
#define WORD_H_

#include <iostream>
#include <string>


class Word {
	std::string word;


public:
	Word() = default;

	explicit Word(std::string word);
	std::ostream &print(std::ostream &out) const;
	std::istream &read(std::istream &in);
	void removeNotAlpha(std::istream &in);
	void writeWord(std::istream &in);
	bool hasStillValidChar(std::istream &in);
	bool isValidWord(std::string word);

	friend inline std::ostream &operator<<(std::ostream &out, Word const &word) {
		return word.print(out);
	}

	friend inline std::istream &operator>>(std::istream &in, Word word) {
		return word.read(in);
	}
};

#endif /* WORD_H_ */
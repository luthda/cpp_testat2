#ifndef WORD_H_
#define WORD_H_

#include <iostream>
#include <string>


class Word {
	std::string word{"default"};

public:
	Word() = default;

	explicit Word(std::string word);
	std::ostream &print(std::ostream &out) const;
	std::istream &read(std::istream &in);
	void removeNotAlpha(std::istream &in);
	void writeWord(std::istream &in);
	bool isValidWord(std::string word) const;
	bool operator<(Word const &rhs) const;
	bool operator==(Word const &rhs) const;

	friend inline std::ostream &operator<<(std::ostream &out, Word const &word) {
		return word.print(out);
	}

	friend inline std::istream &operator>>(std::istream &in, Word &word) {
		return word.read(in);
	}
};

inline bool operator<=(Word const &lhs, Word const &rhs) {
	return !(rhs < lhs);
}

inline bool operator>(Word const &lhs, Word const &rhs) {
	return rhs < lhs;
}
inline bool operator>=(Word const &lhs, Word const &rhs) {
	return !(lhs < rhs);
}

inline bool operator!=(Word const &lhs, Word const &rhs) {
	return !(lhs == rhs);
}

#endif /* WORD_H_ */

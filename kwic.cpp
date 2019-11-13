#include "word.h"
#include "kwic.h"

#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>
#include <set>

namespace text {

	using namespace std;
	using line = vector<Word>;

	line createWordLine(string inputLine) {
		using wordIt = istream_iterator<Word>;
		istringstream strStream{inputLine};
		line retLine{};
		copy(wordIt{strStream}, wordIt{}, back_inserter(retLine));
		return retLine;
	}

	vector<line> getFullText(istream &in) {
		vector<line> fullText{};
		string line{};
		while(getline(in, line)) {
			fullText.push_back(createWordLine(line));
		}
		return fullText;
	}

	set<line> createKwic(vector<line> fullText) {
		set<line> kwic{};
		for_each(cbegin(fullText), cend(fullText), [&kwic](line const currLine){
			line rotatedLine{};
			auto it = begin(currLine);
			while(it != end(currLine)) {
				rotate_copy(begin(currLine), it, end(currLine), std::back_inserter(rotatedLine));
				kwic.insert(rotatedLine);
				rotatedLine.clear();
				++it;
			}
		});
		return kwic;
	}

	void printKwic(set<line> kwic, ostream &out) {
		using wordOut = ostream_iterator<Word>;
		wordOut outIterator{out, " "};
		for_each(cbegin(kwic), cend(kwic), [&out, &outIterator](line const currLine) {
			copy(cbegin(currLine), cend(currLine), outIterator);
			out << '\n';
		});
	}

	void kwic(istream &in, ostream &out){
			set<line> kwic = createKwic(getFullText(in));
			printKwic(kwic, out);
	}
}

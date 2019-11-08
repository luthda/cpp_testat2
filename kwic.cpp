#include "Word.h"
#include "kwic.h"

#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
using namespace text;
using line = vector<Word>;


line createWordLine(string inputLine) {
	using wordIterator = istream_iterator<Word>;
	istringstream strStream{inputLine};
	line retLine{};
	copy(wordIterator{strStream}, wordIterator{}, back_inserter(retLine));
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

vector<line> createkwic(vector<line> fullText) {
	vector<line> kwic{};
	for_each(cbegin(fullText), cend(fullText), [&kwic](line const currLine){
		line rotatedLine{};
		auto it = begin(currLine);
		while(it != end(currLine)) {
			rotate_copy(begin(currLine), it, end(currLine), std::back_inserter(rotatedLine));
			kwic.push_back(rotatedLine);
			rotatedLine.clear();
			++it;
		}
	});
	return kwic;
}

void kwic(istream &in, ostream &out){

}

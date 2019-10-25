#include "Word.h"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <stdexcept>

void testValidWord() {
	std::ostringstream output{};
	Word word{"Word"};
	word.print(output);
	ASSERT_EQUAL("Word", output.str());
}

void testInvalidWord() {
	ASSERT_THROWS(Word{";)"}, std::invalid_argument);
}

void testEmptyWord() {
	ASSERT_THROWS(Word{"  "}, std::invalid_argument);
}

void testPrintStream() {
	std::ostringstream output{};
	std::istringstream input{"Test-Works"};
	Word word{};
	input >> word;
	word.print(output);
	ASSERT_EQUAL("Test", output.str());
}

void testPrintTwoWordStream() {
	std::ostringstream output{};
	std::istringstream input{"Test-Works"};
	Word word{};
	input >> word;
	input >> word;
	word.print(output);
	ASSERT_EQUAL("Works", output.str());
}

void testPrintStreamMultiple() {
	std::ostringstream output{};
	std::istringstream input{"Test-Works"};
	Word word{};
	input >> word;
	input >> word;
	input >> word;
	word.print(output);
	ASSERT_EQUAL("Works", output.str());
}

void testOutStream() {
	std::ostringstream output{};
	std::istringstream input{"Test-Works___Nice"};
	Word word{};
	input >> word;
	input >> word;
	input >> word;
	output << word;
	ASSERT_EQUAL("Nice", output.str());
}

void testGreaterThan() {
	Word word1{"xD"};
	Word word2{"xO"};
	ASSERT(word2 > word1);
}

void testGreaterThanOrEqual() {
	Word word1{"xD"};
	Word word2{"xO"};
	Word word3{"XD"};
	ASSERT(word3 >= word1);
	ASSERT(word2 >= word1);

}

void testEqual() {
	Word word1{"xD"};
	Word word2{"XD"};
	ASSERT(word1 == word2);
}

void testNotEqual() {
	Word word1{"xD"};
	Word word2{"xO"};
	ASSERT(word2 != word1);
}

void testSmaller() {
	Word word1{"xD"};
	Word word2{"xO"};
	ASSERT(word1 < word2);
}

void testSmallerOrEqual() {
	Word word1{"xD"};
	Word word2{"xO"};
	Word word3{"XD"};
	ASSERT(word1 <= word3);
	ASSERT(word1 <= word2);
}

void thisIsATest() {
	ASSERTM("start writing tests", true);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	s.push_back(CUTE(testPrintStream));
	s.push_back(CUTE(testPrintStreamMultiple));
	s.push_back(CUTE(testOutStream));
	s.push_back(CUTE(testPrintTwoWordStream));
	s.push_back(CUTE(testValidWord));
	s.push_back(CUTE(testInvalidWord));
	s.push_back(CUTE(testEmptyWord));
	s.push_back(CUTE(testGreaterThan));
	s.push_back(CUTE(testGreaterThanOrEqual));
	s.push_back(CUTE(testEqual));
	s.push_back(CUTE(testNotEqual));
	s.push_back(CUTE(testSmaller));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}

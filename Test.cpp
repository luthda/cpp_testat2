#include "Word.h"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <stdexcept>

void testPrintStream() {
	std::ostringstream output{};
	std::istringstream input{"Test-Works"};
	Word word{};
	input >> word;
	word.print(output);
	ASSERT_EQUAL("Test", output.str());
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
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}

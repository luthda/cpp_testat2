#include "Word.h"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void testPrintWord() {
	std::ostringstream output{};
	std::string input{"Test-Works"};
	Word word{input};
	word.print(output);
	ASSERT_EQUAL("Works", output.str());
}

void testWordStream() {
	std::ostringstream output{};
	std::istringstream input{"Test-Works"};
	Word word{};
	input >> word;
	word.print(output);
	ASSERT_EQUAL("Works", output.str());
}

void thisIsATest() {
	ASSERTM("start writing tests", true);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	s.push_back(CUTE(testWordStream));
	s.push_back(CUTE(testPrintWord));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}


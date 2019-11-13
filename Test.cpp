#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "word.h"
#include "kwic.h"
#include <stdexcept>

using namespace text;

void testValidWord() {
	std::ostringstream output{};
	Word word{"Word"};
	word.print(output);
	ASSERT_EQUAL("Word", output.str());
}

void testValidWord2() {
	std::ostringstream output{};
	Word word{"Word"};
	ASSERT_EQUAL(Word{"Word"}, word);
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

void test_cannot_create_empty_word() {
	ASSERT_THROWS(Word { "" }, std::invalid_argument);
}

void test_cannot_create_word_with_space() {
	ASSERT_THROWS(Word { "abc xyz" }, std::invalid_argument);
}

void test_cannot_create_word_with_number() {
	ASSERT_THROWS(Word { "abc3xyz" }, std::invalid_argument);
}

void test_cannot_create_word_with_punctuation() {
	ASSERT_THROWS(Word { "abc.xyz" }, std::invalid_argument);
}

void test_output_operator() {
	std::string const expected { "Python" };
	Word const w { expected };
	std::ostringstream output { };
	output << w;
	ASSERT_EQUAL(expected, output.str());
}

void test_same_words_are_equal() {
	ASSERT_EQUAL(Word { "Ruby" }, Word { "Ruby" });
}

void test_different_words_are_not_equal() {
	ASSERT_NOT_EQUAL_TO(Word{"Haskell"}, Word{"ML"});
}

void test_same_word_with_different_cases_are_equal() {
	ASSERT_EQUAL(Word { "BASIC" }, Word { "basic" });
}

void test_same_word_is_not_lower_than() {
	ASSERT(!(Word { "Erlang" } < Word { "Erlang" }));
}

void test_smaller_word_is_smaller() {
	ASSERT_LESS(Word { "Erlang" }, Word { "Fortran" });
}

void test_smaller_word_with_capital_letters_is_smaller() {
	ASSERT_LESS(Word { "ADA" }, Word { "java" });
}

void test_same_word_with_different_cases_are_not_smaller() {
	ASSERT(!(Word {"Groovy"} < Word {"groovy"}));
}

void test_greater_word_is_greater() {
	ASSERT_GREATER(Word { "Rust" }, Word { "Prolog" });
}

void test_greater_word_with_capital_letters_is_greater() {
	ASSERT_GREATER(Word { "Lisp" }, Word { "brainfuck" });
}

void test_smaller_word_is_less_equal() {
	ASSERT_LESS_EQUAL(Word { "Algol" }, Word { "BCPL" });
}

void test_same_word_is_less_equal() {
	ASSERT_LESS_EQUAL(Word { "Assembler" }, Word { "Assembler" });
}

void test_greater_word_is_greater_equal() {
	ASSERT_GREATER_EQUAL(Word { "RPG" }, Word { "Perl" });
}

void test_same_word_is_greater_equal() {
	ASSERT_GREATER_EQUAL(Word { "Scala" }, Word { "Scala" });
}

void test_input_operator_single_word() {
	std::istringstream input{"Elixir"};
	Word w{};
	input >> w;
	ASSERT_EQUAL(Word{"Elixir"}, w);
}

void test_input_operator_single_word_stream_good() {
	std::istringstream input{"Cobol"};
	Word w{};
	ASSERT(input >> w);
}

void test_input_operator_called_once_first_word() {
	std::istringstream input{"Ceylon Go"};
	Word w{};
	input >> w;
	ASSERT_EQUAL(Word{"Ceylon"}, w);
}

void test_input_operator_called_once_stream_good() {
	std::istringstream input{"Lua Oberon"};
	Word w{};
	ASSERT(input >> w);
}

void test_input_operator_on_empty_stream_fail() {
	std::istringstream input{};
	Word w{};
	input >> w;
	ASSERT(input.fail());
}

void test_input_operator_on_stream_without_word() {
	std::istringstream input{"1337"};
	Word w{};
	input >> w;
	ASSERT(input.fail());
}

void test_input_operator_on_empty_stream_word_unchanged() {
	std::istringstream input{};
	Word w{"Eiffel"};
	input >> w;
	ASSERT_EQUAL(Word{"Eiffel"}, w);
}

void test_input_operator_stops_on_slash() {
	std::istringstream input{"PL/SQL"};
	Word w{};
	input >> w;
	ASSERT_EQUAL(Word{"PL"}, w);
}

void test_input_operator_stops_at_end_of_word() {
	std::istringstream input{"VB6"};
	Word w{};
	int i{};
	input >> w >> i;
	ASSERT_EQUAL(6, i);
}

void test_input_operator_skips_leading_non_alpha() {
	std::istringstream input{"3switchBF"};
	Word w{};
	input >> w;
	ASSERT_EQUAL(Word{"switchBF"}, w);
}

void test_input_operator_overwrites_word() {
	std::istringstream input{"Kotlin"};
	Word w{"JavaScript"};
	input >> w;
	ASSERT_EQUAL(Word{"Kotlin"}, w);
}

void test_exercise_example() {
	std::istringstream input{"compl33tely ~ weird !!??!! 4matted in_put"};
	Word w{};
	input >> w;
	ASSERT_EQUAL(Word{"compl"}, w);
	input >> w;
	ASSERT_EQUAL(Word{"tely"}, w);
	input >> w;
	ASSERT_EQUAL(Word{"weird"}, w);
	input >> w;
	ASSERT_EQUAL(Word{"matted"}, w);
	input >> w;
	ASSERT_EQUAL(Word{"in"}, w);
	input >> w;
	ASSERT_EQUAL(Word{"put"}, w);
	input >> w;
	ASSERT_EQUAL(Word{"put"}, w);
}

void test_kwic_easy() {
	std::istringstream input{"this is only a easy test"};
	std::ostringstream output{};
	kwic(input, output);
	ASSERT_EQUAL(
			"a easy test this is only \n"
			"easy test this is only a \n"
			"is only a easy test this \n"
			"only a easy test this is \n"
			"test this is only a easy \n"
			"this is only a easy test \n", output.str());
}

void test_kwic_example() {
	std::istringstream input{"this is a test \n this is another test"};
	std::ostringstream output{};
	kwic(input, output);
	ASSERT_EQUAL(
			"a test this is \n"
			"another test this is \n"
			"is a test this \n"
			"is another test this \n"
			"test this is a \n"
			"test this is another \n"
			"this is a test \n"
			"this is another test \n", output.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	s.push_back(CUTE(testValidWord));
	s.push_back(CUTE(testValidWord2));
	s.push_back(CUTE(testInvalidWord));
	s.push_back(CUTE(testEmptyWord));
	s.push_back(CUTE(testPrintStream));
	s.push_back(CUTE(testPrintTwoWordStream));
	s.push_back(CUTE(testOutStream));
	s.push_back(CUTE(testGreaterThan));
	s.push_back(CUTE(testGreaterThanOrEqual));
	s.push_back(CUTE(testEqual));
	s.push_back(CUTE(testNotEqual));
	s.push_back(CUTE(testSmaller));
	s.push_back(CUTE(testSmallerOrEqual));
	s.push_back(CUTE(test_cannot_create_empty_word));
	s.push_back(CUTE(test_cannot_create_word_with_space));
	s.push_back(CUTE(test_cannot_create_word_with_number));
	s.push_back(CUTE(test_cannot_create_word_with_punctuation));
	s.push_back(CUTE(test_output_operator));
	s.push_back(CUTE(test_same_words_are_equal));
	s.push_back(CUTE(test_different_words_are_not_equal));
	s.push_back(CUTE(test_same_word_with_different_cases_are_equal));
	s.push_back(CUTE(test_same_word_is_not_lower_than));
	s.push_back(CUTE(test_smaller_word_is_smaller));
	s.push_back(CUTE(test_smaller_word_with_capital_letters_is_smaller));
	s.push_back(CUTE(test_same_word_with_different_cases_are_not_smaller));
	s.push_back(CUTE(test_greater_word_with_capital_letters_is_greater));
	s.push_back(CUTE(test_smaller_word_is_less_equal));
	s.push_back(CUTE(test_greater_word_is_greater));
	s.push_back(CUTE(test_same_word_is_less_equal));
	s.push_back(CUTE(test_greater_word_is_greater_equal));
	s.push_back(CUTE(test_same_word_is_greater_equal));
	s.push_back(CUTE(test_input_operator_single_word));
	s.push_back(CUTE(test_input_operator_single_word_stream_good));
	s.push_back(CUTE(test_input_operator_called_once_first_word));
	s.push_back(CUTE(test_input_operator_called_once_stream_good));
	s.push_back(CUTE(test_input_operator_on_empty_stream_fail));
	s.push_back(CUTE(test_input_operator_on_stream_without_word));
	s.push_back(CUTE(test_input_operator_on_empty_stream_word_unchanged));
	s.push_back(CUTE(test_input_operator_stops_on_slash));
	s.push_back(CUTE(test_input_operator_stops_at_end_of_word));
	s.push_back(CUTE(test_input_operator_skips_leading_non_alpha));
	s.push_back(CUTE(test_input_operator_overwrites_word));
	s.push_back(CUTE(test_exercise_example));
	s.push_back(CUTE(test_kwic_easy));
	s.push_back(CUTE(test_kwic_example));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}

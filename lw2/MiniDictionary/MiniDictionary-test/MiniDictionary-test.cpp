#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MiniDictionary/modules.h"

SCENARIO("Find word in dictionary")
{
	Dictionary dictionary = { { {"cat"}, {"кот", "кошка"} } };
	std::string word1 = "cat";
	std::string word2 = "кот";
	REQUIRE(FindTermInDictionary(word1, dictionary));
	REQUIRE(FindTermInDictionary(word2, dictionary));
}

SCENARIO("Add word with translations in dictionary")
{
	Dictionary dictionary;
	std::string word = "ancient";
	std::string translation1 = "древний";
	std::string translation2 = "старинный";
	bool foundWord = false;
	AddWordWithTranslationInDictionary(foundWord, dictionary, word, translation1);
	REQUIRE(FindTranslationInDictionary(word, translation2, dictionary));
	Dictionary result = { {{"ancient"}, {"древний", "старинный"}} };
	REQUIRE(dictionary == result);
}

SCENARIO("Parse string while reading dictionary")
{
	std::string line = "грустный, печальный, скорбный, горестный, унылый, тоскливый, плачевный, прискорбный, досадный, мрачный";
	std::vector<std::string> wordsInLine = ParseString(line);
	std::vector<std::string> result = { "грустный", "печальный", "скорбный", "горестный", "унылый", "тоскливый", "плачевный", "прискорбный", "досадный", "мрачный"};
	REQUIRE(result == wordsInLine);
}
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MiniDictionary/modules.h"

SCENARIO("Find word in dictionary")
{
	Dictionary dictionary = { { {"cat"}, {"кот", "кошка"} } };
	std::string word1 = "cat";
	std::string word2 = "кот";
	bool foundWord = false;
	std::string messageToUser = FindTermInDictionary(word1, dictionary, foundWord);
	REQUIRE(foundWord);
	foundWord = false;
	messageToUser = FindTermInDictionary(word2, dictionary, foundWord);
	REQUIRE(foundWord);
}

SCENARIO("Add word with translations in dictionary")
{
	Dictionary dictionary;
	std::string word = "ancient";
	std::string translation1 = "древний";
	std::string translation2 = "старинный";
	bool foundWord = false;
	std::string messageToUser;
	messageToUser = AddWordWithTranslationInDictionary(foundWord, dictionary, word, translation1, messageToUser);
	foundWord = false;
	messageToUser = FindTranslationInDictionary(word, translation2, dictionary, foundWord);
	REQUIRE(foundWord);
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
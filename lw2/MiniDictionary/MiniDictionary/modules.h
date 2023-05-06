#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <windows.h>
#include <optional>

struct Args
{
	std::string input;
};

using Dictionary = std::map<std::vector<std::string>, std::vector<std::string>>;

std::string Str_tolower(std::string s);
bool IsEnglishWord(const std::string& word);
bool FindWordInVector(std::vector<std::string>& words, std::string word);
std::string FindTermInDictionary(std::string& word, Dictionary& dictionary, bool& foundWord);
std::string FindTranslationInDictionary(std::string& translation, std::string& word, Dictionary& dictionary, bool& foundWord);
std::string AddWordWithTranslationInDictionary(bool foundWord, Dictionary& dictionary, std::string& word, std::string& translation, std::string& messageToUser);
void WordInteractWithDictionary(std::string& word, Dictionary& dictionary);
std::vector<std::string> ParseString(std::string& line);
bool ReadDictionaryFromFile(Dictionary& dictionary, std::fstream& input, std::string path);
void UpdateTheDictionary(Dictionary& dictionary, std::fstream& output, const std::string& path);
bool UserInteractionsWithDictionary(std::string path);
std::optional<Args> ParseArgs(int argc, char* argv[]);
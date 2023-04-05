#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <windows.h>
#include <cctype>
#include <utility>
#include <iterator>

typedef std::map<std::vector<std::string>, std::vector<std::string>> Dictionary;

std::string Str_tolower(std::string);
bool IsEnglishWord(const std::string&);
bool FindWordInVector(std::vector<std::string>&, std::string);
bool FindTermInDictionary(std::string&, Dictionary&);
bool FindTranslationInDictionary(std::string&, std::string&, Dictionary&);
void AddWordWithTranslationInDictionary(bool, Dictionary&, std::string&, std::string&);
void TranslateWord(std::string&, Dictionary&);
std::vector<std::string> ParseString(std::string&);
bool ReadFileForDictionary(Dictionary&, std::fstream&, std::string);
void UpdateTheDictionary(Dictionary&, std::fstream&, const std::string&);
bool UserInteractionsWithDictionary();
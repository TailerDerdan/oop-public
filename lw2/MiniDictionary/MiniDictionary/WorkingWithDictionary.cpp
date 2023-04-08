#include "modules.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <iterator>

std::string Str_tolower(std::string s)
{
	std::string result = s;
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
	std::swap(result, s);
	return result;
}

bool IsEnglishWord(const std::string& word)
{
	return (word[0] >= 'A' && word[0] <= 'Z') || (word[0] >= 'a' && word[0] <= 'z');
}

bool FindWordInVector(std::vector<std::string>& words, std::string word)
{
	for (auto iter2 : words)
	{
		if (Str_tolower(word) == Str_tolower(iter2))
		{
			return true;
		}
	}
	return false;
}

std::string ConcatenationWordsFromVector(std::vector<std::string> words)
{
	std::string result;
	for (auto iter : words)
	{
		result.append(iter).append(" ");
	}
	return result;
}

bool FindTermInDictionary(std::string& word, Dictionary& dictionary, std::string& messageToUser)
{
	bool foundWord = false;

	for (auto iter : dictionary)
	{
		std::vector<std::string> terms = iter.first;
		std::vector<std::string> translations = iter.second;
		if (FindWordInVector(terms, Str_tolower(word)))
		{
			foundWord = true;
			messageToUser = ConcatenationWordsFromVector(translations);
			break;
		}
		if (!foundWord)
		{
			if (FindWordInVector(translations, Str_tolower(word)))
			{
				foundWord = true;
				messageToUser = ConcatenationWordsFromVector(terms);
				break;
			}
		}
	}
	return foundWord;
}

bool FindTranslationInDictionary(std::string& translation, std::string& word, Dictionary& dictionary, std::string& messageToUser)
{
	bool foundWord = false;

	for (auto iter : dictionary)
	{
		std::vector<std::string> terms = iter.first;
		std::vector<std::string> translations = iter.second;
		if (FindWordInVector(terms, Str_tolower(translation)))
		{
			foundWord = true;
			translations.push_back(word);
			dictionary.erase(iter.first);
			dictionary.insert(std::make_pair(terms, translations));//TODO: разделить бизнес-логику и общение с пользователем
			messageToUser = "ѕеревод слова '" + translation + "' сохраненен в словаре как '" + word + "'";
			break;
		}
		if (!foundWord)
		{
			if (FindWordInVector(translations, Str_tolower(translation)))
			{
				foundWord = true;
				terms.push_back(word);
				dictionary.erase(iter.first);
				dictionary.insert(std::make_pair(terms, translations));
				messageToUser = "ѕеревод слова '" + translation + "' сохраненен в словаре как '" + word + "'";
				break;
			}
		}
	}
	return foundWord;
}

void AddWordWithTranslationInDictionary(bool foundWord, Dictionary& dictionary, std::string& word, std::string& translation, std::string& messageToUser)
{
	if (!foundWord)
	{
		std::vector<std::string> words;
		std::vector<std::string> translations;
		if (IsEnglishWord(word))
		{
			words.push_back(word);
			translations.push_back(translation);
			dictionary.insert(std::make_pair(words, translations));
			messageToUser = "Cлово '" + word + "' сохраненено в словаре как '" + translation + "'";
		}
		else
		{
			words.push_back(translation);
			translations.push_back(word);
			dictionary.insert(std::make_pair(words, translations));
			messageToUser = "Cлово '" + word + "' сохраненено в словаре как '" + translation + "'";
		}
	}
}

void WordInteractWithDictionary(std::string& word, Dictionary& dictionary)//TODO: метод translate должен только переводить, поигать с терминологией
{
	std::string messageToUser;
	bool foundWord = FindTermInDictionary(word, dictionary, messageToUser);
	
	if (!foundWord)
	{
		std::string translation;

		std::cout << "Ќеизвестное слово '" << word << "'. ¬ведите перевод или пустую строку дл€ отказа." << std::endl;
		std::getline(std::cin, translation);
		if (translation.empty())
		{
			std::cout << "—лово '" << word << "' проигнорировано." << std::endl;
		}
		if (!translation.empty())
		{
			foundWord = FindTranslationInDictionary(translation, word, dictionary, messageToUser);
			AddWordWithTranslationInDictionary(foundWord, dictionary, word, translation, messageToUser);
		}
	}
	std::cout << messageToUser << std::endl;
}

std::vector<std::string> ParseString(std::string& line)
{
	std::vector<std::string> result;
	const std::string DELIMITER = ", ";
	std::string word;
	size_t pos = 0;

	while ((pos = line.find(DELIMITER)) != std::string::npos) {
		word = line.substr(0, pos);
		result.push_back(word);
		line.erase(0, pos + DELIMITER.length());
	}
	result.push_back(line);
	return result;
}

bool ReadDictionaryFromFile(Dictionary& dictionary, std::fstream& input, std::string path)//TODO: ReadDicFromFile
{
	input.open(path);

	if (!input.is_open())
	{
		std::cout << "Failed to open '" << path << "' for reading\n";
		return false;
	}

	std::string line;
	const char OPENING_BRACKET = '[';//TODO: use const
	const char CLOSING_BRACKET = ']';

	while (std::getline(input, line))
	{
		if (!line.empty())
		{
			size_t posOpeningBracket = line.find_first_of(OPENING_BRACKET);
			size_t posClosingBracket = line.find_first_of(CLOSING_BRACKET);
			std::string terms = line.substr(posOpeningBracket + 1, posClosingBracket - posOpeningBracket - 1);

			posClosingBracket = line.find_first_of(CLOSING_BRACKET);
			std::string translations = line.substr(posClosingBracket + 2, line.size() - 3);

			dictionary.insert(std::make_pair(ParseString(terms), ParseString(translations)));
		}
	}
	return true;
}

void UpdateTheDictionary(Dictionary& dictionary, std::fstream& output, const std::string& path)
{
	output.close();
	output.open(path);

	const char OPENING_BRACKET = '[';
	const char CLOSING_BRACKET = ']';

	for (auto iter : dictionary)
	{
		output << OPENING_BRACKET;
		copy(iter.first.begin(), iter.first.end() - 1, std::ostream_iterator<std::string>(output, ", "));
		output << iter.first.at(iter.first.size() - 1);
		output << CLOSING_BRACKET << ' ';
		copy(iter.second.begin(), iter.second.end() - 1, std::ostream_iterator<std::string>(output, ", "));
		output << iter.second.at(iter.second.size() - 1);
		output << std::endl;
	}
}

bool UserInteractionsWithDictionary(std::string path)
{
	//TODO: должен передаватьс€ как аргумент
	std::fstream fileDictionary;
	Dictionary dictionary;

	if (!ReadDictionaryFromFile(dictionary, fileDictionary, path))
	{
		return false;
	}

	std::string word;
	const std::string END = "...";//TODO: const
	bool transferCount = false;//TODO: use boolean

	while (std::getline(std::cin, word))
	{
		if (word == END)
		{
			break;
		}
		//TODO: remove
		WordInteractWithDictionary(word, dictionary);
		transferCount = true;
	}
	char ch;
	if (transferCount)
	{
		std::cout << "¬ словарь были внесены изменени€. ¬ведите Y или y дл€ сохранени€ перед выходом." << std::endl;
		std::cin >> ch;
		if (ch == 'Y')
		{
			UpdateTheDictionary(dictionary, fileDictionary, path);
		}
		if (ch == 'y')
		{
			std::cout << "»зменени€ не сохранены. ƒо свидани€." << std::endl;
		}
	}
	return true;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count" << std::endl << "Usage: MiniDictionary.exe <dictionary.txt>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.input = argv[1];
	return args;
}
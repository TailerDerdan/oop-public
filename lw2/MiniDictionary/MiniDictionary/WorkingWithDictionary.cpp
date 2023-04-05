#include "modules.h"

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

bool FindTermInDictionary(std::string& word, Dictionary& dictionary)
{
	bool foundWord = false;

	for (auto iter : dictionary)
	{
		std::vector<std::string> terms = iter.first;
		std::vector<std::string> translations = iter.second;
		if (FindWordInVector(terms, Str_tolower(word)))
		{
			foundWord = true;
			copy(translations.begin(), translations.end(), std::ostream_iterator<std::string>(std::cout, " "));
			std::cout << std::endl;
			break;
		}
		if (!foundWord)
		{
			if (FindWordInVector(translations, Str_tolower(word)))
			{
				foundWord = true;
				copy(terms.begin(), terms.end(), std::ostream_iterator<std::string>(std::cout, " "));
				std::cout << std::endl;
				break;
			}
		}
	}
	return foundWord;
}

bool FindTranslationInDictionary(std::string& translation, std::string& word, Dictionary& dictionary)
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
			dictionary.insert(std::make_pair(terms, translations));
			std::cout << "������� ����� '" << translation << "' ���������� � ������� ��� '" << word << "'" << std::endl;
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
				std::cout << "������� ����� '" << translation << "' ���������� � ������� ��� '" << word << "'" << std::endl;
				break;
			}
		}
	}
	return foundWord;
}

void AddWordWithTranslationInDictionary(bool foundWord, Dictionary& dictionary, std::string& word, std::string& translation)
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
			std::cout << "C���� '" << word << "' ����������� � ������� ��� '" << translation << "'" << std::endl;
		}
		else
		{
			words.push_back(translation);
			translations.push_back(word);
			dictionary.insert(std::make_pair(words, translations));
			std::cout << "C���� '" << word << "' ����������� � ������� ��� '" << translation << "'" << std::endl;
		}
	}
}

void TranslateWord(std::string& word, Dictionary& dictionary)
{
	bool foundWord = FindTermInDictionary(word, dictionary);
	
	if (!foundWord)
	{
		std::string translation;

		std::cout << "����������� ����� '" << word << "'. ������� ������� ��� ������ ������ ��� ������." << std::endl;
		std::getline(std::cin, translation);
		if (translation.empty())
		{
			std::cout << "����� '" << word << "' ���������������." << std::endl;
		}
		if (!translation.empty())
		{
			foundWord = FindTranslationInDictionary(translation, word, dictionary);
			AddWordWithTranslationInDictionary(foundWord, dictionary, word, translation);
		}
	}
}

std::vector<std::string> ParseString(std::string& line)
{
	std::vector<std::string> result;
	std::string delimiter = ", ";
	std::string word;
	size_t pos = 0;

	while ((pos = line.find(delimiter)) != std::string::npos) {
		word = line.substr(0, pos);
		result.push_back(word);
		line.erase(0, pos + delimiter.length());
	}
	result.push_back(line);
	return result;
}

bool ReadFileForDictionary(Dictionary& dictionary, std::fstream& input, std::string path)
{
	input.open(path);

	if (!input.is_open())
	{
		std::cout << "Failed to open '" << path << "' for reading\n";
		return false;
	}

	std::string line;
	char openingBracket = '[';
	char closingBracket = ']';

	while (std::getline(input, line))
	{
		if (!line.empty())
		{
			size_t posOpeningBracket = line.find_first_of(openingBracket);
			size_t posClosingBracket = line.find_first_of(closingBracket);
			std::string terms = line.substr(posOpeningBracket + 1, posClosingBracket - posOpeningBracket - 1);

			posClosingBracket = line.find_first_of(closingBracket);
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

	char openingBracket = '[';
	char closingBracket = ']';

	for (auto iter : dictionary)
	{
		output << openingBracket;
		copy(iter.first.begin(), iter.first.end() - 1, std::ostream_iterator<std::string>(output, ", "));
		output << iter.first.at(iter.first.size() - 1);
		output << closingBracket << ' ';
		copy(iter.second.begin(), iter.second.end() - 1, std::ostream_iterator<std::string>(output, ", "));
		output << iter.second.at(iter.second.size() - 1);
		output << std::endl;
	}
}

bool UserInteractionsWithDictionary()
{
	std::string path = "dictionary.txt";
	std::fstream fileDictionary;
	Dictionary dictionary;

	if (!ReadFileForDictionary(dictionary, fileDictionary, path))
	{
		return false;
	}

	std::string word;
	std::string end = "...";
	int transferCount = 0;

	while (std::getline(std::cin, word))
	{
		if (word == end)
		{
			break;
		}
		bool err = false;
		TranslateWord(word, dictionary);
		transferCount++;
	}
	char ch;
	if (transferCount != 0)
	{
		std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������." << std::endl;
		std::cin >> ch;
		if (ch == 'Y')
		{
			UpdateTheDictionary(dictionary, fileDictionary, path);
		}
		if (ch == 'y')
		{
			std::cout << "��������� �� ���������. �� ��������." << std::endl;
		}
	}
	return true;
}
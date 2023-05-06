#include "modules.h"
#include <regex>
#include <cctype>

//всегда возвращать значение функции
//с большой буквы
//по константной ссылке
Protocol GetProtocolByString(const std::string& protocol_str)
{
	if (protocol_str == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocol_str == "https")
	{
		return Protocol::HTTPS;
	}
	else if (protocol_str == "ftp")
	{
		return Protocol::FTP;
	}
	return Protocol::Invalid;
}

//всегда возвращать значение функции
int GetDefaultPortByProtocol(const std::string& protocol_str)
{
	if (protocol_str == "http")
	{
		return 80;
	}
	else if (protocol_str == "https")
	{
		return 443;
	}
	else if (protocol_str == "ftp")
	{
		return 21;
	}
	return EXIT_FAILURE;
}

std::string Str_tolower(std::string s)
{
	std::string result = s;
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
	std::swap(result, s);
	return result;
}

//вынести url в отдельную переменную типа string
bool ParseURL(URL& urlStruct, std::string& url)
{
	url = Str_tolower(url);
	std::regex urlRegex(R"(((https?|ftp):\/\/)([^\/:]+)(?::(\d+))?(\/\S*)?)"); //должно быть без учета регистра

	std::smatch urlMatch;

	if (std::regex_match(url, urlMatch, urlRegex))
	{
		std::string protocolStr = urlMatch[2].str();
		urlStruct.host = urlMatch[3].str();
		urlStruct.protocol = GetProtocolByString(protocolStr);
		if (urlStruct.protocol == Protocol::Invalid)
		{
			return false;
		}

		if (!urlMatch[4].str().empty())
		{
			urlStruct.port = std::stoi(urlMatch[4].str());
			if (urlStruct.port < 1 || urlStruct.port > 65535)
			{
				return false;
			}
		}

		if (urlMatch[4].str().empty())
		{
			urlStruct.port = GetDefaultPortByProtocol(protocolStr);
			if (urlStruct.port == EXIT_FAILURE)
			{
				return false;
			}
		}
		
		if (!urlMatch[5].str().empty())
		{
			urlStruct.document.append(urlMatch[5].str(), 1, urlMatch[5].str().size() - 1);
		}
		return true;
	}//убрать else
	return false;
}

//переименовать функцию
void OutputInfoAboutUrl(URL& urlStruct)
{
	std::cout << "HOST: " << urlStruct.host << std::endl;
	std::cout << "PORT: " << urlStruct.port << std::endl;
	std::cout << "DOC: " << urlStruct.document << std::endl;
}

void ParsingUrl()
{
	URL urlStruct;
	std::string url;

	while (std::getline(std::cin, url))
	{
		if (!ParseURL(urlStruct, url))
		{
			std::cout << "Invalid URL" << std::endl;
			continue;
		}
		OutputInfoAboutUrl(urlStruct);
	}	
}
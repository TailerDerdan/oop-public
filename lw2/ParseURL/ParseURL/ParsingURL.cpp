#include "modules.h"
#include <regex>

void ChangeProtocol(Protocol& protocol, std::string& protocol_str)
{
	if (protocol_str == "http")
	{
		protocol = HTTP;
	}
	else if (protocol_str == "https")
	{
		protocol = HTTPS;
	}
	else if (protocol_str == "ftp")
	{
		protocol = FTP;
	}
}

void ChangePort(int& port, std::string& protocol_str)
{
	if (port == 0)
	{
		if (protocol_str == "http")
		{
			port = 80;
		}
		else if (protocol_str == "https")
		{
			port = 443;
		}
		else if (protocol_str == "ftp")
		{
			port = 21;
		}
	}
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex url_regex(R"(((https?|ftp):\/\/)([^\/:]+)(?::(\d+))?(\/\S*)?)", std::regex_constants::icase);

	std::smatch url_match;

	if (std::regex_match(url, url_match, url_regex)) {
		std::string protocol_str = url_match[2].str();
		host = url_match[3].str();
		ChangeProtocol(protocol, protocol_str);

		if (!url_match[4].str().empty())
		{
			port = std::stoi(url_match[4].str());
		}
		if (url_match[4].str().empty())
		{
			ChangePort(port, protocol_str);
		}
		
		if (!url_match[5].str().empty())
		{
			document.append(url_match[5].str(), 1, url_match[5].str().size() - 1);
		}
	}
	else {
		return false;
	}
	return true;
}

void OutputPort(Protocol& protocol, int& port, std::string host, std::string& document)
{
	std::cout << "HOST: " << host << std::endl;
	std::cout << "PORT: " << port << std::endl;
	std::cout << "DOC: " << document << std::endl;
}
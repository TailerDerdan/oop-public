#include <iostream>
#include <regex>
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

std::string Port(Protocol& protocol)
{
	std::string result;
	
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex url_regex(R"(((https?|ftp):\/\/)([^\/:]+)(?::(\d+))?(\/\S*)?)", std::regex_constants::icase);

	std::smatch url_match;

	if (std::regex_match(url, url_match, url_regex)) {
		std::string host_name = url_match[2].str();
		std::string port = url_match[4].str();
		std::string file_path = url_match[5].str();

		std::cout << "Host name: " << host_name << std::endl;
		std::cout << "Port: " << (port.empty() ? "80" : port) << std::endl;
		std::cout << "File path: " << (file_path.empty() ? "/" : file_path) << std::endl;
		return true;
	}
	else {
		std::cout << "Invalid URL" << std::endl;
		return false;
	}
}


int main() {

	std::string url = "ftp://www.mysite.com:9081/docs/document1.html?page=30&lang=en#title";

	return 0;
}
#include "modules.h"

int main() {

	std::string url = "ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;

	if (!ParseURL(url, protocol, port, host, document))
	{
		std::cout << "Invalid URL" << std::endl;
		return EXIT_FAILURE;
	}
	OutputPort(protocol, port, host, document);

	return EXIT_SUCCESS;
}
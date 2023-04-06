#include "modules.h"

int main() {

	std::string url = "ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;

	ParseURL(url, protocol, port, host, document);
	OutputPort(protocol, port, host, document);

	return 0;
}
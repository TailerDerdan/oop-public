#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../ParseURL/modules.h"

SCENARIO("Parse URL with port")
{
	std::string url = "ftp://www.mysite.com:9801/docs/document1.html?page=30&lang=en#title";
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;

	REQUIRE(ParseURL(url, protocol, port, host, document));
	REQUIRE(protocol == FTP);
	REQUIRE(port == 9801);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

SCENARIO("Parse URL without port")
{
	std::string url = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;

	REQUIRE(ParseURL(url, protocol, port, host, document));
	REQUIRE(protocol == HTTPS);
	REQUIRE(port == 443);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

SCENARIO("Parse URL without document")
{
	std::string url = "https://www.mysite.com";
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;

	REQUIRE(ParseURL(url, protocol, port, host, document));
	REQUIRE(protocol == HTTPS);
	REQUIRE(port == 443);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document.empty());
}

SCENARIO("Not correct URL")
{
	std::string url = "htps:/";
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;

	REQUIRE(!ParseURL(url, protocol, port, host, document));
}
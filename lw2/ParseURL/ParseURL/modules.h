#pragma once

#include <iostream>
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
	Invalid
};

struct URL
{
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;
};

Protocol GetProtocolByString(const std::string& protocol_str);
int GetDefaultPortByProtocol(const std::string&);
bool ParseURL(URL& urlStruct, const std::string& url);
void OutputInfoAboutUrl(URL& urlStruct);
void ParsingUrl();
#pragma once

#include <iostream>
#include <regex>
#include <string>

enum Protocol
{
	HTTP,
	HTTPS,
	FTP
};

void ChangePortAndProtocol(Protocol&, int&, std::string&);
bool ParseURL(std::string const&, Protocol&, int&, std::string&, std::string&);
void OutputPort(Protocol&, int&, std::string, std::string&);
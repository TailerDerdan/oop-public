#pragma once

#include <iostream>
#include <string>

enum Protocol
{
	HTTP,
	HTTPS,
	FTP
};

void ChangePort(int&, std::string&);
bool ParseURL(std::string const&, Protocol&, int&, std::string&, std::string&);
void OutputPort(Protocol&, int&, std::string, std::string&);
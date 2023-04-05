#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>

std::string DecodeSpecialChar(std::string&, bool&);
std::string HtmlDecode(const std::string&, bool&);
void ReadText(std::string&);
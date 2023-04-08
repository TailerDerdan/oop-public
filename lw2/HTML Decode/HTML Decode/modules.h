#pragma once
//оставить только те, которые нужно при передачи в функции
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>
#include <map>

//указать имена параметров
std::string DecodeSpecialChar(std::string&);
std::string HtmlDecode(const std::string&);
void ReadText(std::string&);
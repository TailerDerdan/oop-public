#pragma once
//�������� ������ ��, ������� ����� ��� �������� � �������
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>
#include <map>

//������� ����� ����������
std::string DecodeSpecialChar(std::string&);
std::string HtmlDecode(const std::string&);
void ReadText(std::string&);
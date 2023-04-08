#pragma once
#include <iostream>
#include <set>
#include <optional>
#include <string>

struct Args
{
	std::string upperBound;
};

std::set<int> TheSieveOfEratosfen(int);
std::optional<Args> ParseArgs(int argc, char* argv[]);
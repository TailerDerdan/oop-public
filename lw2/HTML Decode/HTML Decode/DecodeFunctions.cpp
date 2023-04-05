#include "modules.h"

std::string DecodeSpecialChar(std::string& temp, bool& wasError)
{
	if (temp == "&quot;")
	{
		return "\"";
	}
	if (temp == "&apos;")
	{
		return "'";
	}
	if (temp == "&gt;")
	{
		return ">";
	}
	if (temp == "&lt;")
	{
		return "<";
	}
	if (temp == "&amp;")
	{
		return "&";
	}
	else
	{
		wasError = true;
		return " ";
	}
}

std::string HtmlDecode(const std::string& html, bool& err)
{
	if (html.empty())
	{
		return html;
	}
	std::string result = html;
	size_t pos = 0;
	size_t curPosSpecialChar = 0;
	size_t nextPosSpecialChar = 0;

	while (curPosSpecialChar <= result.length() && nextPosSpecialChar <= result.length())
	{
		curPosSpecialChar = result.find('&', curPosSpecialChar);
		pos = curPosSpecialChar;
		nextPosSpecialChar = result.find(';', curPosSpecialChar);

		std::string temp;
		temp.append(result, pos, nextPosSpecialChar - curPosSpecialChar + 1);

		std::string specialChar = DecodeSpecialChar(temp, err);
		if (err)
		{
			std::cout << "There is no such html entity - " << temp << std::endl;
			return result;
		}
		result.replace(curPosSpecialChar, temp.size(), specialChar);
		curPosSpecialChar++;
	}
	return result;
}

void ReadText(std::string& text)
{
	std::string line;
	while (!std::cin.eof())
	{
		std::getline(std::cin, line);
		text.append(line);
	}
}
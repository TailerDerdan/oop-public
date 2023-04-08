#include "modules.h"

std::string DecodeSpecialChar(std::string& temp)
{
	std::map<std::string, std::string> specialChar{ {"&quot;", "\""}, { "&apos;", "'" }, 
	{ "&gt;", ">" }, { "&lt;", "<" }, { "&amp;", "&" } };

	for (auto iter : specialChar)
	{
		if (temp == iter.first)
		{
			return iter.second;
		}
	}

	return temp;
}

std::string HtmlDecode(const std::string& html)
{
	if (html.empty())
	{
		return html;
	}
	std::string result;
	size_t pos = 0;
	size_t curPosSpecialChar = 0;
	size_t nextPosSpecialChar = 0;

	while (curPosSpecialChar <= html.length() && nextPosSpecialChar <= html.length())
	{
		pos = curPosSpecialChar;
		curPosSpecialChar = html.find('&', curPosSpecialChar);
		nextPosSpecialChar = html.find(';', curPosSpecialChar);

		// изменить имя перемменой
		std::string potentialHTMLEnt;
		if (curPosSpecialChar <= html.length())
		{
			potentialHTMLEnt.append(html, curPosSpecialChar, nextPosSpecialChar - curPosSpecialChar + 1);
		}

		//не должна возвращать ошибок
		if (!potentialHTMLEnt.empty())
		{
			std::string specialChar = DecodeSpecialChar(potentialHTMLEnt);
			result.append(html, pos, curPosSpecialChar - pos).append(specialChar);
			curPosSpecialChar+=potentialHTMLEnt.size();
		}
		if (potentialHTMLEnt.empty())
		{
			result.append(html, pos, html.size() - pos);
		}
		//формировать новую строку, а не модифицировать существующую
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
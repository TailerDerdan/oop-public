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
	std::string tempHtml = html;
	size_t pos = 0;
	size_t curPosSpecialChar = 0;
	size_t nextPosSpecialChar = 0;

	while (curPosSpecialChar <= tempHtml.length() && nextPosSpecialChar <= tempHtml.length())
	{
		pos = curPosSpecialChar;
		curPosSpecialChar = tempHtml.find('&', curPosSpecialChar);
		nextPosSpecialChar = tempHtml.find(';', curPosSpecialChar);
		
		std::string temp;
		temp.append(tempHtml, pos, nextPosSpecialChar - curPosSpecialChar + 1);

		std::string specialChar = DecodeSpecialChar(temp, err);
		if (err)
		{
			std::cout << "There is no such html entity - " << temp << std::endl;
			return tempHtml;
		}
		tempHtml.replace(curPosSpecialChar, temp.size(), specialChar);
		curPosSpecialChar++;
	}
	return tempHtml;
}

int main()
{
	std::string text;
	std::copy(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), std::back_inserter(text));

	bool err = false;
	text = HtmlDecode(text, err);
	if (err)
	{
		return EXIT_FAILURE;
	}

	copy(text.begin(), text.end(), std::ostream_iterator<char>(std::cout));

	return EXIT_SUCCESS;
}
#include "modules.h"

int main()
{
	std::string text;
	ReadText(text);

	text = HtmlDecode(text);

	copy(text.begin(), text.end(), std::ostream_iterator<char>(std::cout));

	return EXIT_SUCCESS;
}
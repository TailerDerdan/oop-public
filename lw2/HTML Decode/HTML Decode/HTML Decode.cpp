#include "modules.h"

int main()
{
	std::string text;
	ReadText(text);

	bool err = false;
	text = HtmlDecode(text, err);
	if (err)
	{
		return EXIT_FAILURE;
	}

	copy(text.begin(), text.end(), std::ostream_iterator<char>(std::cout));

	return EXIT_SUCCESS;
}
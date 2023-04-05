#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HTML Decode/modules.h"

SCENARIO("Empty string give empty string")
{
	bool err = false;
	REQUIRE(HtmlDecode("", err).empty());
}

SCENARIO("Test with all special characters")
{
	bool err = false;
	std::string result = HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s", err);
	REQUIRE(result == "Cat <says> \"Meow\". M&M\'s");
}

SCENARIO("Test with multiline text")
{
	bool err = false;
	std::string result = HtmlDecode("The third most popular book of all time, &quot;Harry Potter&quot;, has sold over 400,000,000 copies &amp;\n\&apos;Titanic&apos; is a 1997 movie directed by James Cameron about the sinking of the ship &lt;Titanic&gt;.", err);
	REQUIRE(result == "The third most popular book of all time, \"Harry Potter\", has sold over 400,000,000 copies &\n'Titanic' is a 1997 movie directed by James Cameron about the sinking of the ship <Titanic>.");
}
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HTML Decode/modules.h"

SCENARIO("Empty string give empty string")
{
	REQUIRE(HtmlDecode("").empty());
}

SCENARIO("Test with all special characters")
{
	std::string result = HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
	REQUIRE(result == "Cat <says> \"Meow\". M&M\'s");
}

SCENARIO("Test with multiline text")
{
	std::string result = HtmlDecode("The third most popular book of all time, &quot;Harry Potter&quot;, has sold over 400,000,000 copies &amp;\n\&apos;Titanic&apos; is a 1997 movie directed by James Cameron about the sinking of the ship &lt;Titanic&gt;.");
	REQUIRE(result == "The third most popular book of all time, \"Harry Potter\", has sold over 400,000,000 copies &\n'Titanic' is a 1997 movie directed by James Cameron about the sinking of the ship <Titanic>.");
}

SCENARIO("Test without html entity")
{
	std::string result = HtmlDecode("A real hero human being");
	REQUIRE(result == "A real hero human being");
}

//проверить работу на строках без html сущностей
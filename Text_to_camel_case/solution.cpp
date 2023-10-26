#include <string>

// CamelCase is a style of writing compound words in which multiple 
// words are written consecutively without spaces, with each word within a phrase capitalized.

class ToCamelCase
{
public:
	std::string toCamelCase(std::string text) 
	{
		for (int i = 0; i < text.length(); i++)
		{
			// Checking that a character is not a letter.
			if (!isalpha(text[i]))
			{
				// To avoid the case of consecutive special characters, we need to use a while loop, 
				// removing each special character.
				while (!isalpha(text[i]))
				{
					text.erase(text.find(text[i]), 1);
				}

				// If no special character is found, the next ariori character is a letter, 
				// so the toupper() function must be used.
				text[i] = toupper(text[i]);
			}
		}

		return text;
	}
};

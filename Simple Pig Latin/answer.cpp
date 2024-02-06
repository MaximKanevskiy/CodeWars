#include <string>
#include <sstream>
#include <cctype>

std::string pig_it(std::string str)
{
    std::stringstream ss(str);
    std::string word;
    std::string result;

    while (ss >> word)
    {
        if (ispunct(word[0]))
        {
            result += word + " ";
            continue;
        }

        word = word.substr(1, -1) + word.substr(0, 1) + "ay";
        result += word + " ";
    }

    result.pop_back();

    return result;
}

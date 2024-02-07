#include <string>
#include <algorithm>
#include <unordered_map>

std::string duplicate_encoder(const std::string& word) 
{
	std::unordered_map<char, int> char_counts;
	std::string result;
	std::string lower_case_word = word;
	std::transform(lower_case_word.begin(), lower_case_word.end(), lower_case_word.begin(), ::tolower);

	for (char letter : lower_case_word)
	{
		char_counts[letter]++;
	}

	for (char letter : lower_case_word)
	{
		result += char_counts[letter] > 1 ? ")" : "(";
	}

	return result;
}

#include <string>
#include <vector>

std::size_t duplicateCount(const std::string& in)
{
	size_t count = 0;
	std::vector<char> checked;

	for (int i = 0; i < in.length(); i++)
	{
		for (int j = 0; j < in.length(); j++)
		{
			char current = tolower(in[j]);

			if (find(checked.begin(), checked.end(), current) != checked.end())
			{
				continue;
			}

			if (tolower(in[i]) == current && i != j)
			{
				count++;
				checked.push_back(tolower(in[j]));
				break;
			}
		}
	}

	return count;
}

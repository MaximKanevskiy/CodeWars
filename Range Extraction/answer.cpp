#include <iostream>
#include <string>
#include <vector>

void cleverConcat(std::vector<int> vec, std::string& str)
{
	if (vec.size() > 2)
	{
		str += std::to_string(vec[0]) + "-" + std::to_string(vec.back()) + ",";
	}
	else
	{
		for (size_t j = 0; j < vec.size(); j++)
		{
			str += std::to_string(vec[j]) + ",";
		}
	}
}

std::string range_extraction(std::vector<int> args)
{
	std::vector<int> temp;
	std::string result;

	for (size_t i = 0; i < args.size(); i++)
	{
		if (temp.empty() || args[i] - args[i - 1] == 1)
		{
			temp.push_back(args[i]);
			continue;
		}

		if (args[i] - args[i - 1] > 1)
		{
			cleverConcat(temp, result);

			temp.clear();
			i--;
		}
	}

	if (!temp.empty())
	{
		cleverConcat(temp, result);
	}

	result.pop_back();

	return result;
}

#include <string>
#include <algorithm>

static std::string add(const std::string& a, const std::string& b) 
{
	std::string num1 = a;
	std::string num2 = b;
	std::reverse(num1.begin(), num1.end());
	std::reverse(num2.begin(), num2.end());

	std::string result;

	int carry = 0;
	int size = std::max(num1.length(), num2.length());
	int sum = 0;
	char digit_num1, digit_num2;

	for (int i = 0; i < size; i++)
	{
		digit_num1 = i < num1.length() ? num1[i] : '0';
		digit_num2 = i < num2.length() ? num2[i] : '0';

		sum = (digit_num1 - '0') + (digit_num2 - '0') + carry;
		carry = sum / 10;
		result += std::to_string(sum % 10);
	}

	if (carry != 0)
	{
		result += std::to_string(carry);
	}

	std::reverse(result.begin(), result.end());

	return result;
}

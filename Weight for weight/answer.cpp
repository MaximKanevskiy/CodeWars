#include <string>
#include <sstream>
#include <set>
#include <algorithm>

class WeightSort
{
private:
    static bool compare(const std::string& num1, const std::string& num2)
    {
        int w_num1 = CalcWeight(num1);
        int w_num2 = CalcWeight(num2);

        if (w_num1 != w_num2) return w_num1 < w_num2;

        return num1 < num2;
    }
public:
    static int CalcWeight(const std::string& num)
    {
        int sum = 0;

        for (const char& digit : num)
        {
            sum += digit - '0';
        }

        return sum;
    }

    static std::string orderWeight(const std::string& strng)
    {
        if (strng.empty()) return "";

        std::multiset<std::string, bool(*)(const std::string&, const std::string&)> numbers(compare);

        std::stringstream ss(strng);
        std::string num;

        while (ss >> num)
        {
            numbers.insert(num);
        }

        std::string result;

        for (const auto& number : numbers)
        {
            result += number + " ";
        }

        result.pop_back();

        return result;
    }
};

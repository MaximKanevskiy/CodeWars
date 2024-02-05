#include <string>
#include <vector>
#include <map>
#include <stack>

class DirReduction
{
public:
    static bool is_opposite(const std::string& direction1, const std::string& direction2) 
    {
        std::map<std::string, std::string> opposite = {
            {"NORTH", "SOUTH"},
            {"SOUTH", "NORTH"},
            {"EAST", "WEST"},
            {"WEST", "EAST"}
        };

        return opposite[direction1] == direction2;
    }

    static std::vector<std::string> dirReduc(std::vector<std::string>& arr)
    {
        std::stack<std::string> current_direction;

        for (size_t i = 0; i < arr.size(); i++)
        {
            if (current_direction.empty())
            {
                current_direction.push(arr[i]);
                continue;
            }

            if (is_opposite(arr[i], current_direction.top()))
            {
                current_direction.pop();
            }
            else
            {
                current_direction.push(arr[i]);
            }
        }

        std::vector<std::string> reduced_direction;
        while (!current_direction.empty())
        {
            reduced_direction.push_back(current_direction.top());
            current_direction.pop();
        }

        std::reverse(reduced_direction.begin(), reduced_direction.end());

        return reduced_direction;
    }
};

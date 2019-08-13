#include "../include/helper.hpp"

#include <iostream>
#include <algorithm>

void helper::fatal_error(std::string error_msg)
{
    std::cerr << "Error: " << error_msg << "!" << std::endl;
    std::exit(1);
}

std::vector<std::string> helper::split(std::string str)
{
    std::vector<std::string> result;

    auto i = str.cbegin();
    while (i != str.cend()) {
        i = std::find_if_not(i, str.cend(), isspace);
        
        auto j = std::find_if(i, str.cend(), isspace);

        if (i != str.cend())
            result.push_back(std::string(i, j));

        i = j;
    }

    return result;
}

bool helper::is_variable(std::string var)
{
    return !(isdigit(var[0]) > 0);
}

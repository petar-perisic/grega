#ifndef HELPER_HPP_
#define HELPER_HPP_

#include <vector>
#include <string>

class helper {
public:
    static void fatal_error(std::string error_msg);
    static std::vector<std::string> split(std::string str);
    static bool is_variable(std::string var);
};

#endif // HELPER_HPP_

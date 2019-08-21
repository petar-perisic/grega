#ifndef instruction_manager_HPP_
#define instruction_manager_HPP_

#include "instruction.hpp"

#include <fstream>
#include <string>
#include <vector>

class instruction_manager {
public:
    instruction_manager(std::string & file_path);

    std::vector<instruction> & instructions() const;

    void load_instructions();

    void liveness_analysis();

private:
    std::ifstream m_file;
    
    std::vector<instruction> m_instructions;

    instruction parse_instruction(std::string & instruction_string);
};

#endif // instruction_manager_HPP_

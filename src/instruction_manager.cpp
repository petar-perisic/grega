#include "../include/instruction_manager.hpp"
#include "../include/helper.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

instruction_manager::instruction_manager(std::string & file_path)
    : m_file(file_path, std::ios::in)
{
    if (file_path.empty())
        helper::fatal_error("Missing operand!\nTry 'grega --help' for more information");

    if (!m_file.is_open())
        helper::fatal_error("Opening test file failed");
}

std::vector<instruction> & instruction_manager::instructions()
{
    return m_instructions;
}

std::vector<instruction> instruction_manager::load_instructions()
{
    std::string instruction_string;
    while (std::getline(m_file, instruction_string)) {
        m_instructions.push_back(parse_instruction(instruction_string));
    }

    return m_instructions;
}

instruction instruction_manager::parse_instruction(std::string & instruction_string)
{
    auto instruction_parts = helper::split(instruction_string);
    
    instruction i(std::move(instruction_parts[0]));
    if (instruction_parts.size() == 5) { // x = y op z
        i.size(3);
        i.operand1(std::move(instruction_parts[2]));
        i.instruction_operator(std::move(instruction_parts[3]));
        i.operand2(std::move(instruction_parts[4]));
    }

    else if (instruction_parts.size() == 3) { // x = y
        i.size(1);
        i.operand1(std::move(instruction_parts[2]));
    }

    return i;
}

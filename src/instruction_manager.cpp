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

void instruction_manager::load_instructions()
{
    std::string instruction_string;
    while (std::getline(m_file, instruction_string)) {
        m_instructions.push_back(parse_instruction(instruction_string));
    }   
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

void instruction_manager::liveness_analysis()
{
    int size = m_instructions.size();
    for (auto i = m_instructions.rbegin(); i != m_instructions.rend(); i++) {
        if (!i->is_moved()) {
            if (i != m_instructions.rbegin())
                i->use() = (i - 1)->use();
        
            // remove variable from the left hand side
            auto del = std::find(i->use().begin(), i->use().end(), i->var());
            if (del != i->use().end())
                i->use().erase(del);

            // add operators on the right hand side
            if (i->size() == 3) {
                i->use_list_add_if_unique(i->operand1());
                i->use_list_add_if_unique(i->operand2());
            } else {
                 i->use_list_add_if_unique(i->operand1());
            }

            #ifdef DEBUG 
            std::cout << "Liveness analysis:" << std::endl;
            std::cout << size-- << ". " << i->to_string() << std::endl;
            i->print_use_list();
            #endif // DEBUG
        }
    }
}

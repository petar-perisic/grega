#include "../include/instruction_loader.hpp"

#include <iostream>

namespace grega {
    
instruction_loader::instruction_loader(std::string & file_path)
    : m_file(file_path)
{}

} // namespace grega

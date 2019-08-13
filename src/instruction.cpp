#include "../include/instruction.hpp"

namespace grega {
    
instruction::instruction(std::string & name, std::string & body)
    : m_name(name), m_body(body)
{
    parse_body();
}

void instruction::parse_body()
{
    //auto strings = std::string::sp
}

} // namespace grega

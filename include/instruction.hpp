#ifndef INSTRUCTION_HPP_
#define INSTRUCTION_HPP_

#include <string>
#include <vector>

namespace grega {

class instruction {
public:
    instruction(std::string & name, std::string & body);

    std::string to_string() const;

private:
    std::string m_name;
    
    std::string m_body;

    std::string m_operand1;
    std::string m_operand2;
    char m_operator;

    void parse_body();
};

} // namespace grega

#endif // INSTRUCTION_HPP_
#ifndef INSTRUCTION_HPP_
#define INSTRUCTION_HPP_

#include <string>
#include <vector>
#include <iterator>

class instruction {
public:
    instruction(std::string && var_name);

    std::string to_string() const;

    void size(int n);
    int size() const;
    
    void operand1(std::string && op);
    void operand2(std::string && op);
    
    std::string var() const;
    std::string operand1() const;
    std::string operand2() const;

    void instruction_operator(std::string && op);
    std::string instruction_operator() const;

    void use(std::vector<std::string> && vars);
    std::vector<std::string>& use();

    void is_move_var(bool option);
    bool is_move_var() const;

    void is_move_op1(bool option);
    bool is_move_op1() const;

    void is_move_op2(bool option);
    bool is_move_op2() const;

    void use_list_add_if_unique(std::string operand);
    
    void print_use_list() const;

private:
    std::string m_var;
    
    std::string m_operand1;
    std::string m_operand2;
    
    std::string m_operator;

    int m_size;

    std::vector<std::string> m_use;
    
    bool m_move_var = false;
    bool m_move_op1 = false;
    bool m_move_op2 = false;
};

#endif // INSTRUCTION_HPP_

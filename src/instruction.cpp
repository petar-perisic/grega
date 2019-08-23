#include "../include/instruction.hpp"
#include "../include/helper.hpp"

#include <algorithm>
#include <iostream>
#include <utility>

instruction::instruction(std::string && var_name)
    : m_var(var_name)
{}

std::string instruction::to_string() const
{
    return m_size == 3 ?    
        m_var + " := " + m_operand1 + " " + m_operator + " " + m_operand2 :
        m_var + " := " + m_operand1;
}

void instruction::size(int n)
{
    m_size = n;
}

int instruction::size() const
{
    return m_size;   
}

void instruction::operand1(std::string && op)
{
    m_operand1 = std::move(op);
}

void instruction::operand2(std::string && op)
{
    m_operand2 = std::move(op);
}

std::string instruction::var() const
{
    return m_var;
}

std::string instruction::operand1() const
{
    return m_operand1;
}

std::string instruction::operand2() const
{
    return m_operand2;
}

void instruction::instruction_operator(std::string && op)
{
    m_operator = std::move(op);
}

std::string instruction::instruction_operator() const
{
    return m_operator;
}

void instruction::use(std::vector<std::string> && vars)
{
    m_use = std::move(vars);
}

std::vector<std::string>& instruction::use()
{
    return m_use;
}

void instruction::is_move_var(bool option)
{
    m_move_var = option;
}

bool instruction::is_move_var() const
{
    return m_move_var;
}

void instruction::is_move_op1(bool option)
{
    m_move_op1 = option;
}

bool instruction::is_move_op1() const
{
    return m_move_op1;
}

void instruction::is_move_op2(bool option)
{
    m_move_op2 = option;
}

bool instruction::is_move_op2() const
{
    return m_move_op2;
}

void instruction::use_list_add_if_unique(std::string operand)
{
    auto cond = std::find(m_use.begin(), m_use.end(), operand);
    if (cond == m_use.end()) { // not found in use list
        if (helper::is_variable(operand))
            m_use.push_back(operand);
    }
}

void instruction::print_use_list() const
{
    std::cout << "\tuse: [ ";
    for (auto i : m_use)
        std:: cout << i << " ";
    std::cout << "]";

    std::cout << "\n" << std::endl;
}

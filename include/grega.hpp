#ifndef GREGA_HPP_
#define GREGA_HPP_

#include "instruction.hpp"
#include "graph.hpp"

#include <vector>
#include <string>

class grega {
public:
    Graph static build(std::vector<instruction> & instruction_set);
};

#endif // GREGA_HPP_
#ifndef GREGA_HPP_
#define GREGA_HPP_

#include "instruction.hpp"
#include "graph.hpp"
#include "node.hpp"
#include <vector>
#include <string>

class grega {
public:
    graph static build(std::vector<instruction> & instruction_set);
    void static simplify_spill(graph & G);
    
    void static select(graph & G);
    void static start_over(node u);
    
    void static print(const graph & G);

    static std::vector<node> spill_nodes;
    static int reg_num;


private:
    bool static color(node & u, graph & G);
    void static erase_color(std::vector<int> & colors, int color);

    static std::vector<instruction> instruction_set;
};

#endif // GREGA_HPP_
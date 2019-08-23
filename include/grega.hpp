#ifndef GREGA_HPP_
#define GREGA_HPP_

#include "instruction.hpp"
#include "graph.hpp"
#include "node.hpp"
#include <vector>
#include <string>

class grega {
public:
    void static liveness_analysis();

    graph static build();
    void static simplify_spill(graph & G);
    
    void static select(graph & G);
    void static start_over(node u);
    
    void static print(graph & G);

    static std::vector<node> spill_nodes;
    static int reg_num;
    
    static std::vector<instruction> instruction_set;

private:
    bool static color(node & u, graph & G);
    void static erase_color(std::vector<int> & colors, int color);
};

#endif // GREGA_HPP_
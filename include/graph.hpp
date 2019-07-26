#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <vector>

namespace grega {

class graph {
public:
    graph();

    void add_edge(const int u, const int v);

    void print() const;

private:
    std::map<std::string, std::vector<int>> adjacency_list;
};

} // namespace grega

#endif // GRAPH_HPP

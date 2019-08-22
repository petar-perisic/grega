#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>
#include <string>

class node {
public:
    node();
    node(std::string name);

    void name(std::string node_name);
    std::string name() const;

    void color(int col);
    int color() const;

    int degree(std::vector<std::pair<node, node>> adjacency_list);
    int degree() const;

    bool operator==(const node & other) const;

    void is_spilled(bool option);
    bool is_spilled() const;

    std::vector<node> & adjacent_nodes();

private:
    std::string m_name;
    int m_color = 0;
    int m_degree = 0;
    bool m_is_spilled = false;

    std::vector<node> m_adjacent_nodes;
};

#endif // NODE_HPP_
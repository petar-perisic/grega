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

    void color(std::string col);
    std::string color() const;

    int degree(std::vector<std::pair<node, node>> adjacency_list);

    bool operator==(const node & other) const;

private:
    std::string m_name;
    std::string m_color;
    int m_degree = 0;
};

#endif // NODE_HPP_
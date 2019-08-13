#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>

namespace  grega {

class node {
public:
    node(std::string & name);

    void colour(std::string & colour);

private:
    std::string m_name;
    std::string m_colour = nullptr;
};

} // namespace grega

#endif // NODE_HPP_
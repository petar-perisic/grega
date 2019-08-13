#include "../include/node.hpp"

namespace grega {
    
node::node(std::string & name)
    : m_name(name)
{}

void node::colour(std::string & colour)
{
    m_colour = colour;
}

} // namespace grega

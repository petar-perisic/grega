#ifndef INSTRUCTION_LOADER_HPP_
#define INSTRUCTION_LOADER_HPP_

#include "instruction.hpp"

#include <string>
#include <vector>

namespace grega {

class instruction_loader {
public:
    instruction_loader(std::string & file_path);

private:
    std::string m_file;
    std::vector<instruction> m_instructions;
};

} // namespace grega

#endif // INSTRUCTION_LOADER_HPP_
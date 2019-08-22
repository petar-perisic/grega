#include "../include/instruction_manager.hpp"
#include "../include/instruction.hpp"
#include "../include/graph.hpp"
#include "../include/grega.hpp"

#include <iostream>

#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>

void test_graph();

bool parse_command_line_args(int argc, const char *argv[], std::string & test_file, int & reg_num) 
{
    try {
        boost::program_options::options_description desc{"Options"};
        desc.add_options()
            ("help,h", "Show help")
            ("file,f", boost::program_options::value<std::string>(), "Path to test file")
            ("registers,r", boost::program_options::value<int>(),"Number of available registers");

        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);

        if (vm.count("help")) {
            std::cout << std::endl << desc << std::endl;
            std::exit(1);
        } 
        if (vm.count("file")) {
            test_file = vm["file"].as<std::string>();
        }
        if (vm.count("registers")) {
            reg_num = vm["registers"].as<int>();
        }
    }
    catch (const std::exception & ex) {
        std::cerr << "[Error]: " << ex.what() << "\n";
        return false;
    }

    return true;
}

int main(int argc, char const *argv[])
{
    std::string file_path;

    if (!parse_command_line_args(argc, argv, file_path, grega::reg_num)) 
    {
        std::exit(1);
    }

    instruction_manager manager(file_path);

    manager.load_instructions();

    graph g;
    do {
        manager.liveness_analysis();
        g = grega::build(manager.instructions());
        grega::simplify_spill(g);
        grega::select(g);
    } while (!grega::spill_nodes.empty());

    grega::print(g);
    
    return 0;
}

#include "../include/instruction_loader.hpp"
#include "../include/graph.hpp"
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>

void test_graph();

bool parse_command_line_args(int argc, const char *argv[], std::string & test_file, uint & reg_num) 
{
    try {
        boost::program_options::options_description desc{"Options"};
        desc.add_options()
            ("help", "Show help")
            ("file", boost::program_options::value<std::string>()->required(), "Path to test file")
            ("registers", boost::program_options::value<uint>(),"Number of available registers");

        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);

        if (vm.count("help")) {
            std::cout << "Usage: grega --file [path/to/file] --registers [number_of_registers]" << std::endl;
            std::cout << std::endl << desc << std::endl;
            std::exit(1);
        } 
        if (vm.count("file")) {
            test_file = vm["file"].as<std::string>();
        }
        if (vm.count("registers")) {
            reg_num = vm["registers"].as<uint>();
        }
    }
    catch (const std::exception & ex) {
        std::cerr << "[Error]: " << ex.what() << '\n';
        return false;
    }

    return true;
}

int main(int argc, char const *argv[])
{
    /*
    uint reg_num = 16;
    std::string file_path;

    if (!parse_command_line_args(argc, argv, file_path, reg_num)) 
    {
        std::exit(1);
    }

    grega::instruction_loader loader(file_path);

    */
    test_graph();
    return 0;
}

void test_graph(){
    Graph g;
    g.add_node('A');
    g.add_node('B');
    g.add_edge('A', 'B');
    g.add_node('c');
    g.add_node('d');
    g.add_node('e');
    g.add_edge('e', 'a');
    g.add_edge('a', 'd');
    g.add_edge('d', 'a');
    g.add_edge('f', 'g');
    g.add_edge('C', 'A');

    g.print_graph();
}

#include "../include/instruction_manager.hpp"

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>

bool parse_command_line_args(int argc, const char *argv[], std::string & test_file, uint & reg_num) 
{
    try {
        boost::program_options::options_description desc{"Options"};
        desc.add_options()
            ("help,h", "Show help")
            ("file,f", boost::program_options::value<std::string>(), "Path to test file")
            ("registers,r", boost::program_options::value<uint>(),"Number of available registers");

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
    uint reg_num = 16;
    std::string file_path;

    if (!parse_command_line_args(argc, argv, file_path, reg_num))
        std::exit(1);

    instruction_manager manager(file_path);
    manager.load_instructions();
    manager.liveness_analysis();

    return 0;
}

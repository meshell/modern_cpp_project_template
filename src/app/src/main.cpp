#include "my_project/project_library_version.h"
#include "my_project/dummy.h"

#include <boost/program_options.hpp>

#include <iostream>

using my_project::Dummy;
using boost::program_options::options_description;
using boost::program_options::parse_command_line;

int main(int argc, const char** argv) {
    options_description option_description{"Allowed options"};
    option_description.add_options()
            ("help,h", "produce help message")
            ("version", "show version");

    boost::program_options::variables_map variable_map;
    boost::program_options::store(parse_command_line(argc, argv, option_description),
                                  variable_map);
    boost::program_options::notify(variable_map);

    if (variable_map.count("help") > 0) {
        std::cout << option_description << std::endl;
        return 1;
    }

    if (variable_map.count("version") > 0) {
        std::cout << "version: "
                  << my_project::version_major
                  << "."
                  << my_project::version_minor
                  << "."
                  << my_project::version_patch
                  << std::endl;
        return 1;
    }

    Dummy english_dummy{"Hello", "World"};

    std::cout << "A english dummy says: " << english_dummy.say_hello() << std::endl;
    return 0;
}

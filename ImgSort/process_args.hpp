#pragma once

#include <boost/program_options.hpp>
#include <string>

namespace imgsort {

namespace args {

namespace po = boost::program_options;

extern int exit_status;
extern po::options_description all, help;
extern po::variables_map var;

extern std::string usage;

// Print the full usage + options catalog of the program.
void print_usage();

// Initialize options descriptions all and help.
void init_options();

// Returns true if processing should resume, as all options
// were correctly processed and no help type option was given.
bool parse_args(int argc, char** argv);

}

}
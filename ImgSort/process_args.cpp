#pragma once

#include "global.hpp"
#include "process_args.hpp"
#include "sort.hpp"

#include <boost/program_options.hpp>
#include <iostream>

namespace imgsort {

namespace args {

int exit_status = 0;
po::options_description all, help("Options");
po::variables_map var;

std::string usage = "usage:\n"
"      imgsort [<options>] <collectionname>\n"
"      imgsort [<options>] <collectionname> <collectionfolder>\n"
"\n"
"In the first syntax the collection folder is assumed to be\n"
"the current working directory. The image file names must follow\n"
"the syntax collectionname-%d.* (case insensitive) and have\n"
"extension JPEG, PNG, BMP or GIF.\n\n";

void print_usage() {
    std::cout << usage << help << std::endl;
}

void init_options() {
    po::options_description methods("Sorting Methods");
    po::options_description modifiers("Modifiers");
    po::options_description output("Output");
    po::options_description input("Hidden");

    methods.add_options()
        ("huesort", po::value<long>(&sortX)->implicit_value(0), "Index images by hue value, "
         "starting at a given hue value(defaults to 0). This is the default sorting method")
         ("redsort,R", po::value<long>(&sortX)->implicit_value(0), "Sort images by red color "
         "channel, starting a given red (defauls to 0)")
         ("greensort,G", po::value<long>(&sortX)->implicit_value(0), "Sort images by green color "
         "channel, starting a given green (defaults to 0)")
        ("bluesort,B", po::value<long>(&sortX)->implicit_value(0), "Sort images by blue color "
        "channel, starting a given blue (defaults to 0)");

    modifiers.add_options()
        ("reverse", po::bool_switch(&reverseSwitch),
        "Sort images by descending index value (effectively reversing their would-be order)");

    output.add_options()
        ("out,o", po::value<fs::path>(&outputDir), "Direct output "
        "to this directory")
        ("width", po::value<size_t>(&fill_width)->default_value(3), "The total number of digits for "
        "the numerals. Small numerals are padded with 0s")
        ("newname", po::value<std::string>(&outputCollection), "Change the collection's name")
        ("copy", po::bool_switch(&copySwitch), "Copy the images to the output directory instead of "
        "just moving them there")
        ("help,h", po::bool_switch(&helpSwitch), "Show this usage message")
        ("usage", po::bool_switch(&helpSwitch), "Show this usage message");

    input.add_options()
        ("input-collection", po::value<std::string>(&inputCollection), "")
        ("input-dir", po::value<fs::path>(&inputDir), "");

    all.add(methods).add(modifiers).add(output).add(input);
    help.add(methods).add(modifiers).add(output);
}

bool parse_args(int argc, char** argv) {
    po::positional_options_description pos;
    pos.add("input-collection", 1).add("input-dir", 2);

    try {
        po::store(
            po::command_line_parser(argc, argv).options(all).positional(pos).run(),
            var);
        po::notify(var);
    } catch (po::error &e) {
        std::cout << "Error: " << e.what() << std::endl;
        print_usage();
        return false;
    }

    // If no input collection is given, exit.
    if (!var.count("input-collection")) {
        print_usage();
        return false;
    }

    // If Help is requested, exit immediately
    if (helpSwitch) {
        print_usage();
        return false;
    }

    // Override default Sorting Method
    if (var.count("redsort")) {
        indexer = index::redsort;
        selected_indexer = "redsort";
    } else if (var.count("greensort")) {
        indexer = index::greensort;
        selected_indexer = "greensort";
    } else if (var.count("bluesort")) {
        indexer = index::bluesort;
        selected_indexer = "bluesort";
    }

    // Input Directory default
    if (!var.count("input-dir")) {
        inputDir = fs::current_path();
    }

    // Output Directory default
    if (!var.count("out")) {
        outputDir = inputDir;
    }

    // Output Collection default
    if (!var.count("newname")) {
        outputCollection = inputCollection;
    }

    // If Copy is given, then Output directory or output
    // collection must be given as well
    if (copySwitch && !(var.count("out") || var.count("newname"))) {
        std::cout << "Error: Copy option given with no output-dir or collection name" << std::endl;
        print_usage();
        return false;
    }

    return true;
}

}

}
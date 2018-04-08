#pragma once

#include "global.hpp"
#include "files.hpp"

#include <iostream>
#include <regex>

namespace imgsort {

bool confirm() {
    std::cout << "Confirm ? (Write anything to cancel) ";
    std::string tmp;
    getline(std::cin, tmp);
    return tmp.size() == 0;
}

namespace files {

namespace aux {

bool is_collection_image(fs::path path) {
    const std::regex reg(inputCollection + "-\\d+\\.(?:jpg|png|bmp|gif)", std::regex::icase);
    return fs::is_regular_file(path) && std::regex_match(path.filename().string(), reg);
}

}

void make_image_paths_set() {
    for (auto &p : fs::directory_iterator(inputDir)) {
        fs::path path = p.path();

        if (aux::is_collection_image(path)) {
            image_paths_set.insert(path);
        }
    }
}

void print_directories() {
    if (inputDir != outputDir) {
        std::cout << "Input Directory: " << inputDir << std::endl;
        std::cout << "Output Directory: " << outputDir << std::endl;
    } else {
        std::cout << "Directory: " << inputDir << std::endl;
    }
}

void print_collections() {
    if (inputCollection != outputCollection) {
        std::cout << "Input Collection: " << inputCollection << std::endl;
        std::cout << "Output Collection: " << outputCollection << std::endl;
    } else {
        std::cout << "Collection: " << inputCollection << std::endl;
    }
}

void map_files() {
    if (inputDir != outputDir && !fs::exists(outputDir)) {
        fs::create_directories(outputDir);
    }
    if (copySwitch) {
        copy_files();
    } else {
        if (inputDir != outputDir) {
            move_files();
        } else {
            rename_files();
        }
    }
}

void rename_files() {
    for (auto p : attributed_path) {
        fs::rename(p.first, p.second);
    }
}

void copy_files() {
    for (auto p : attributed_path) {
        fs::copy_file(p.first, p.second);
    }
}

void move_files() {
    for (auto p : attributed_path) {
        fs::rename(p.first, p.second);
    }
}

}

}
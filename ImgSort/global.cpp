#pragma once

#include "global.hpp"
#include "sort.hpp"

namespace imgsort {

namespace fs = std::experimental::filesystem;

using namespace Magick;

// Maps
path_set image_paths_set;
index_path_map attributed_index;
path_path_map attributed_path;

// Methods
indexer_function indexer = index::huesort;
std::string selected_indexer = "huesort";
long sortX = 0;

// Modifiers
bool reverseSwitch = false;

// Output
fs::path outputDir;
std::string outputCollection;
bool copySwitch = false;
bool helpSwitch = false;
size_t fill_width = 3;

// Input
fs::path inputDir;
std::string inputCollection;

}
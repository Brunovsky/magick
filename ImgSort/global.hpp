#pragma once

#include <Magick++.h>
#include <experimental/filesystem>
#include <string>
#include <vector>
#include <map>
#include <set>

#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE

namespace imgsort {

namespace fs = std::experimental::filesystem;

using namespace Magick;

// Maps
using path_set = std::set<fs::path>;
using index_path_map = std::multimap<long, fs::path>;
using path_path_map = std::map<fs::path, fs::path>;

extern path_set image_paths_set;
extern index_path_map attributed_index;
extern path_path_map attributed_path;

// Methods
using indexer_function = long(*)(Image& img);

extern indexer_function indexer;
extern std::string selected_indexer;
extern long sortX;

// Modifiers
extern bool reverseSwitch;

// Output
extern fs::path outputDir;
extern std::string outputCollection;
extern bool copySwitch;
extern bool helpSwitch;
extern size_t fill_width;

// Input
extern fs::path inputDir;
extern std::string inputCollection;

}
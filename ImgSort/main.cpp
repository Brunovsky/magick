#include "global.hpp"
#include "process_args.hpp"
#include "files.hpp"
#include "sort.hpp"

#include <chrono>
#include <iostream>

int main(int argc, char** argv) {
    using namespace imgsort;

    // ***** Initialize
    args::init_options();
    if (!args::parse_args(argc, argv)) return args::exit_status;

    InitializeMagick(argv[0]);
    
    // ***** Print input and output
    files::print_directories();
    files::print_collections();

    // ***** Get image files from input directory
    files::make_image_paths_set();
    std::cout << "Found " << image_paths_set.size() << " matching images." << std::endl;
    if (!confirm()) return 0;

    auto start_time = std::chrono::high_resolution_clock::now();

    // ***** Index images according to sorting methods
    indexify_images();

    // ***** Associate with each image its new path
    make_path_map();

    // ***** Map each image to its new path in the filesystem
    files::map_files();

    // ***** End. Compute elapsed time
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long double> elapsed_time = end_time - start_time;
    std::cout << "Done. Elapsed time: " << elapsed_time.count() << "s" << std::endl;
    return 0;
}
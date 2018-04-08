#pragma once

#include <Magick++.h>
#include <experimental/filesystem>
#include <utility>

namespace imgsort {

// Sort ascending
bool sort_images_cmp(const std::pair<fs::path, long> &img1,
    const std::pair<fs::path, long> &img2);

// Sort descending
bool reverse_sort_images_cmp(const std::pair<fs::path, long> &img1,
    const std::pair<fs::path, long> &img2);

void indexify_images();

void make_path_map();

namespace index {

long huesort(Image &img);

long redsort(Image &img);

long greensort(Image &img);

long bluesort(Image &img);

} // imgsort::index

} // imgsort
#pragma once

#include "global.hpp"
#include "sort.hpp"

#include <math.h>

namespace imgsort {

namespace aux {

std::string to_padded_string(long number, size_t width) {
    std::string res = std::to_string(number);
    if (res.size() >= width) return res;
    else {
        res = std::string(width - res.size(), '0') + res;
        return res;
    }
}

}

// Sort ascending
bool sort_images_cmp(const std::pair<fs::path, long> &img1,
    const std::pair<fs::path, long> &img2) {
    return img1.second < img2.second;
}

// Sort descending
bool reverse_sort_images_cmp(const std::pair<fs::path, long> &img1,
    const std::pair<fs::path, long> &img2) {
    return img1.second > img2.second;
}

void indexify_images() {
    for (auto p : image_paths_set) {
        Image img(p.string());
        const long index = indexer(img);
        attributed_index.insert({index, p});
    }
}

void make_path_map() {
    long path_numeral = 0;

    if (!reverseSwitch) {
        for (auto it = attributed_index.cbegin(); it != attributed_index.cend(); ++it) {
            std::string n = aux::to_padded_string(++path_numeral, fill_width);
            fs::path first = it->second;
            fs::path second = outputDir / (outputCollection + "-" + n + first.extension().string());
            attributed_path[first] = second;
        }
    } else {
        for (auto it = attributed_index.crbegin(); it != attributed_index.crend(); ++it) {
            std::string n = aux::to_padded_string(++path_numeral, fill_width);
            fs::path first = it->second;
            fs::path second = outputDir / (outputCollection + "-" + n + first.extension().string());
            attributed_path[first] = second;
        }
    }
}


namespace index {

// Huesort Indexer
long huesort(Image &img) {
    img.resize(Geometry(1, 1));
    img.colorSpace(HSVColorspace);
    return img.pixelColor(0, 0).quantumRed();
}

// Redsort Indexer
long redsort(Image &img) {
    img.resize(Geometry(1, 1));
    return img.pixelColor(0, 0).quantumRed();
}

// Greensort Indexer
long greensort(Image &img) {
    img.resize(Geometry(1, 1));
    return img.pixelColor(0, 0).quantumGreen();
}

// Bluesort Indexer
long bluesort(Image &img) {
    img.resize(Geometry(1, 1));
    return img.pixelColor(0, 0).quantumBlue();
}

} // imgsort::index

} // imgsort
#pragma once
#include <filesystem>
#include <vector>

struct Block {
    size_t from;
    size_t to;
};
std::vector<Block> split_file(const std::filesystem::path& file, int blocks_count);

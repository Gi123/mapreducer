#include "file_preparation.h"

#include <fstream>
#include <fstream>

std::vector<Block> split_file(const std::filesystem::path& file, int blocks_count) {
    std::vector<Block> result;
    size_t size_file = std::filesystem::file_size(file);
    size_t block_size = size_file / blocks_count;
    std::ifstream stream;
    stream.exceptions(std::ifstream::failbit);
    stream.open(file.native(), std::ios::binary);
    int i = 0;
    for(size_t begin = 0, end = 0; i < blocks_count; ++i, begin = end + 1) {
        stream.seekg(begin + block_size);
        std::string buffer;
        stream >> buffer;
        end = stream.tellg();
        if(end != static_cast<size_t>(-1))
            end = size_file - 1;
        result.push_back(Block{begin,end});
    }
    return result;
}
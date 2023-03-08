#pragma once
#include "file_preparation.h"

#include <vector>
#include <string>
#include <functional>

using mapper = std::function<std::string(std::string, size_t)>;
using reducer = std::function<bool(std::vector<std::string>)>;

bool MapReduce(const std::string& file_name, const std::vector<Block> ranges, 
	size_t prefix_count, int rmun, mapper map_func, reducer reduce_func);
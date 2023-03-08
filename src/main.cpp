#include <iostream>
#include <string>
#include <filesystem>

#include "file_preparation.h"
#include "map_reduce.h"

constexpr int max_prefix_lenght = 100;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Need format <path> <mnum> <rnum>" << std::endl;
        return -1;
    }
    int mnum = std::stoi(argv[2]);
    int rnum = std::stoi(argv[3]);
    if(mnum < 1 || rnum < 1) {
        std::cout << "mnum and rnum must be > 0" << std::endl;
        return -1;
    }
    std::filesystem::path const file(argv[1]);
    std::vector<Block> ranges = split_file(file,mnum);
//
    int prefix_count = 1;
	for (; prefix_count < max_prefix_lenght; ++prefix_count)
	{
		bool res = MapReduce(argv[1], ranges, prefix_count, rnum,
			[](std::string s, size_t count) 
			{
				return s.substr(0, count);
			},
			[](std::vector<std::string> strings) // reduce`
			{
				std::string last_string;
				for (size_t i = 0; i < strings.size(); ++i)
				{
					if (i && strings[i] == last_string)
						return false;

					last_string = strings[i];
				}

				return true;
			});

		if (res) break;
	}
//
	if (prefix_count == max_prefix_lenght)
		std::cout << "Map-reduce error\n";
	else
		std::cout << "Minimal prefix lenght " << prefix_count << std::endl;

}
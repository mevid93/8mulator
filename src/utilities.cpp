#include <fstream>
#include "utilities.hpp"

bool isExistingFile(const std::string filename)
{
    std::ifstream infile(filename);
    return infile.good();
}
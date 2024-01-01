#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <bitset>

// binary string to file
void writeBinaryStringAsBinary(const std::string& binaryString, const std::string& filename);

// read file and output ninary string
std::string readBinaryFileAsString(const std::string& filename);
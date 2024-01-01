#include "binaryDataConvertion.h"

void writeBinaryStringAsBinary(const std::string& binaryString, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing." << std::endl;
        return;
    }

    std::size_t length = binaryString.size();
    outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));

    char byte = 0;
    int bitIndex = 7;
    for (std::size_t i = 0; i < length; ++i) {
        if (binaryString[i] == '1') {
            byte |= (1 << bitIndex);
        }
        bitIndex--;
        if (bitIndex < 0) {
            outFile.write(&byte, sizeof(byte));
            byte = 0;
            bitIndex = 7;
        }
    }
    if (bitIndex != 7) {  // Write the last byte if it was partially filled
        outFile.write(&byte, sizeof(byte));
    }

    outFile.close();
}

std::string readBinaryFileAsString(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return "";
    }

    std::size_t length;
    inFile.read(reinterpret_cast<char*>(&length), sizeof(length));

    std::size_t numFullBytes = length / 8;
    std::size_t remainingBits = length % 8;

    std::vector<char> bytes(numFullBytes + (remainingBits > 0 ? 1 : 0), 0);
    inFile.read(bytes.data(), bytes.size());

    inFile.close();

    std::string binaryString;
    for (std::size_t i = 0; i < numFullBytes; ++i) {
        for (int bitIndex = 7; bitIndex >= 0; --bitIndex) {
            binaryString.push_back((bytes[i] & (1 << bitIndex)) ? '1' : '0');
        }
    }

    if (remainingBits > 0) {
        char lastByte = bytes.back();
        for (int bitIndex = 7; bitIndex >= 7 - (remainingBits - 1); --bitIndex) {
            binaryString.push_back((lastByte & (1 << bitIndex)) ? '1' : '0');
        }
    }

    return binaryString;
}

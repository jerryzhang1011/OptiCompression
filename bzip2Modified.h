#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "bwt.h"
#include "msd.h"
#include "bucket_sort.h"
#include "bwt.h"
#include "mtf.h"
#include "rle.h"
#include "huffman.h"
#include "binaryDataConvertion.h"



class bzip2Modified {
    const std::string mtf_charset = "mtf_charset.txt";
    const std::string huffman_code = "huffman_code.txt";
    std::string code_file;
    std::string original_file;
    std::string getFileName();
    std::string extractFileName (std::string fileName);
    void bzip2Modified_encoding();
    void bzip2Modified_decoding(std::string code_file);
    public:
        void io_driver();
};

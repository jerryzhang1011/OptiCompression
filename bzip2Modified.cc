#include "bzip2Modified.h"

using namespace std;

void bzip2Modified::bzip2Modified_encoding() {
    string source_file_name = "";
    string original_text = "";
    string line = "";
    ifstream iss;
    while (1) {
        cout << "Enter File Name to Encode: ";
        cin >> source_file_name;
        this->original_file = source_file_name;
        this->code_file = this->extractFileName(this->original_file) + ".bin";
        iss.open(source_file_name);
        if (iss.is_open()) { break; }
        cout << "FILE DOES NOT EXIST!" << endl;
    }
    while (getline(iss, line)) {
        original_text += line;
        original_text += '\n';
    }
    if (original_text.back() != '\n') original_text += '\n';

    string a = bwt_encoding(original_text);
    string b = mtf_encoding(a);
    string c = rle_encoding(b);
    string d =  buildHuffmanTree(c);
    writeBinaryStringAsBinary(d, this->code_file);
}

void bzip2Modified:: bzip2Modified_decoding (std::string code_file) {
    this->code_file = code_file;
    string binaryStr = readBinaryFileAsString(this->code_file);
    istringstream iss {binaryStr};
    string a = readAndDecode(iss);
    string b = rle_decode(a);
    string c = mtf_decode(b);
    string t = bwt_decode(c);
    
    // output text;
    cout << "Create a name for your Decoded file." << endl;
    string ofile = this->getFileName();
    this->original_file = ofile;
    ofstream oss {ofile};
    oss << t;

    // remove huffman_code.txt mtf_charset.txt and .bin code file
    bool result1 = filesystem::remove(this->huffman_code);
    bool result2 = filesystem::remove(this->mtf_charset);
    bool result3 = filesystem::remove(this->code_file);
    if (!result1 || !result2 || !result3) { throw "CharSet File Damaged or Does not Exist"; }
}

std::string bzip2Modified::getFileName() {
    string fileName;
    while (1) {
        cout << "Please Enter File Name: ";
        cin >> fileName;
        if (!cin.fail()) { break; }
    }
    return fileName;
}

std::string bzip2Modified::extractFileName (std::string fileName) {
    string result = "";
    for (int i = 0; fileName[i] != '.' && fileName[i]; ++i) result += fileName[i];
    return result;
}

void bzip2Modified::io_driver() {
    std::string input;
    while (true) {
        std::cout << "Encode(E) or Decode(D) or Exit(X): ";
        std::cin >> input;
        if (input == "E" || input == "e") {
            try {
                this->bzip2Modified_encoding();
                std::cout << "Encoding successful." << endl;
                std::cout << "Important!! Your Code File is " << this->code_file << std::endl;
                break;
            } catch(const std::exception& e) {
                std::cerr << "Encoding unsuccessful: " << e.what() << std::endl;
                break;
            } catch(...) {
                std::cerr << "Encoding unsuccessful: Unknown error occurred." << std::endl;
                break;
            }
        } else if (input == "D" || input == "d") {
            try {
                std::cout << "What is the Code File name?" << std::endl;
                std::string filename;
                std::cin >> filename;
                this->bzip2Modified_decoding(filename);
                std::cout << "Decoding successful. The original file is " << this->original_file << std::endl;
                break;
            } catch(const std::exception& e) {
                std::cerr << "Decoding unsuccessful: " << e.what() << std::endl;
                std::exit(EXIT_FAILURE);
            } catch(...) {
                std::cerr << "Decoding unsuccessful: Unknown error occurred." << std::endl;
                std::exit(EXIT_FAILURE);
            }
        } else if (input == "X" || input == "x") {
            std::exit(EXIT_SUCCESS);
        } else {
            std::cout << "Invalid input! Please enter 'E' for encoding or 'D' for decoding." << std::endl;
        }
    }
}




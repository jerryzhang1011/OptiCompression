#include "bwt.h"
#include "msd.h"

using namespace std;

const char end_sentinail = 0;

string front_to_back(const string& s) {
    int s_len = s.length();
    string new_s = "";
    for (int i = 1; i < s_len; ++i) {
        new_s += s[i];
    }
    new_s += s[0];
    return new_s;
}

vector<string> cyclicShifts(const string& s) {
    vector<string> rotations(s.length());
    for (size_t i = 0; i < s.length(); ++i) {
        rotations[i] = s.substr(i) + s.substr(0, i);
    }
    return rotations;
}

// string bwt_encoding(string& text) {
//     if (text[text.length()-1] != end_sentinail) { text += end_sentinail; }
//     vector<string> shifts = cyclicShifts(text);
//     std::sort(shifts.begin(), shifts.end());
//     string code_c = "";
//     for (int i = 0; i < text.length(); ++i) {
//         code_c += shifts.at(i)[text.length()-1];
//     }
//     return code_c;
// }

// optimized
std::string bwt_encoding(std::string& text) {
    text += end_sentinail;
    vector<string> rotations = cyclicShifts(text);

    std::sort(rotations.begin(), rotations.end());
    // msd_radix_sort(rotations);

    // Extract the last column.
    std::string bwt_encoded;
    for (const auto& rotation : rotations) {
        bwt_encoded += rotation.back();
    }

    return bwt_encoded;
}

std::string bwt_decode(const std::string& code) {
    string original_text = "";
    int code_len = code.length();
    vector<std::pair<char, int>> A;

    for (int i = 0; i < code_len; ++i) {
        A.emplace_back(make_pair(code[i], i));
    }

    std::stable_sort(A.begin(), A.end());

    int j = 0;
    for ( ; j < code_len; ++j) {
        if (code[j] == end_sentinail) break;
    }

    while (1) {
        char curr = A.at(j).first;
        if (curr == end_sentinail) break;
        original_text += curr;
        j = A.at(j).second;
    }

    return original_text;
}

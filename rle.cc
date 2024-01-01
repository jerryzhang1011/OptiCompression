#include "rle.h"

using namespace std;

const char A = -101;  // 0
const char B = -102;  // 1
const char end_sentinail = -100;

string toBinary (int num) {
    if (num == 0) return "0";
    string binary = "";
    while (num > 0) {
        binary = std::to_string(num % 2) + binary;
        num = num / 2;
    }
    return binary;
}

string bb2 (int num) {
    string result = toBinary(num + 1);
    result.erase(result.begin());
    return result;
}

string convert_A_B(const string& bb2_str, const char end_sentinail) {
    string result = "";
    for (int i = 0; bb2_str[i]; ++i) {
        if (bb2_str[i] == '0') { result += A; } 
        else { 
            result += B;
        }
        result += end_sentinail;
    }
    return result;
}

int count_0 (const string& text, int start_index, string& code) {
    int count = 0;
    for (int i = start_index; text[i]; i += 2) {
        if (text[i] == '0' || text[i] == A || text[i] == B) { 
            if (text[i] == A) { code += "0"; }
            if (text[i] == B) { code += "1"; }
            count += 1; 
        }
        else { break; }
    }
    return count;
}

string rle_encoding(const string& text) {
    string code_c = "";
    for (int i = 0; text[i]; ++i) {
        if (text[i] != '0') {
            code_c += text[i];
        } else {
            string empty = "";
            int count = count_0(text, i, empty);
            code_c += convert_A_B(bb2(count), end_sentinail);
            i += count * 2 - 1;
        }   
    }
    return code_c;
}

int decode_bb2(string& code) {
    code.insert(0, "1");
    int decimalValue = std::stoi(code, nullptr, 2);
    return decimalValue - 1;
}

string convert_to_0(int num) {
    string result = "";
    for (int i = 0; i < num; ++i) { 
        result += "0";
        result += end_sentinail;
    }
    return result;
}

string rle_decode(const string& code) {
    string original_text = "";
    int code_len = code.length();
    for (int i = 0; i < code_len; ++i) {
        if (code[i] != A && code[i] != B) {
            original_text += code[i];
        } else {
            string partial_code = "";
            int count = count_0(code, i, partial_code);
            original_text += convert_to_0(decode_bb2(partial_code));
            i += count * 2 - 1;
        }
    }
    return original_text;
}

#include "mtf.h"
using namespace std;

const char NULL_CHAR = -100;

vector<char> getCharSet(const string& text) {
    vector<char> result;
    map <char, int> record;
    for (auto& i : text) { record[i] += 1;}
    for (const auto& pair : record) { result.emplace_back(pair.first); }
    return result;
}

int find_char_index(const vector<char>& set, char c) {
    int len = set.size();
    for (int i = len-1; i >= 0; --i) {
        if (set.at(i) == c) { return i; }
    }
    return -1;
}

void move_to_front (vector<char>& s, int index) {
    char temp = s.at(index);
    s.erase(s.begin() + index);
    s.insert(s.begin(), temp);
}

string convert_int_str(int num) {
    ostringstream oss;
    oss << num;
    return oss.str();
}

string mtf_encoding(const string& text) {
    int text_len = text.length();
    string code_c = "";
    vector <char> d = getCharSet(text);
    ofstream oss {"mtf_charset.txt"};
    for (int i = 0; i < text_len; ++i) {
        char curr = text[i];
        int d_index = find_char_index(d, curr);
        string d_index_str = convert_int_str(d_index) + NULL_CHAR;
        code_c += d_index_str;
        move_to_front(d, d_index);
    }
    // write code into "mtf_charset.txt"
    for (int i : d) { oss << i << endl; }
    return code_c;
}

vector<char> readCharSet() {
    ifstream iss {"mtf_charset.txt"};
    if (!iss.good()) { throw std::runtime_error("File does not exist: mtf_charset.txt"); }
    vector<char> result;
    int curr;
    while (iss >> curr) { 
        char c = curr;
        result.emplace_back(c); 
    }
    return result;
}

vector<int> strCode_to_intCode(const std::string& code) {
    vector<int> result;
    string curr = "";
    for (auto i: code) {
        if (i != NULL_CHAR) {
            curr += i;
        } else {
            istringstream iss {curr};
            int num;
            iss >> num;
            result.emplace_back(num);
            curr = "";
        }
    }
    return result;
}

void reverse_mtf(vector<char>& s, int index) {
    if (index == 0) {return;}
    char temp = s.at(0);
    s.erase(s.begin());
    s.insert(s.begin() + index, temp);
}


std::string mtf_decode(const std::string& code) {
    try {
       vector<char> char_set = readCharSet(); 
       vector<int> codes = strCode_to_intCode(code);
        string original_text = "";
        int codes_len = codes.size();
        for (int i = codes_len - 1; i >= 0; --i) {
            original_text.insert(original_text.begin(), char_set.at(0));
            reverse_mtf(char_set, codes.at(i));
        }
        return original_text;
    } catch (const std::runtime_error& e) {
        return e.what();
    }
}

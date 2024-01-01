#include "bucket_sort.h"
using namespace std;

void bucket_sort(vector<string>& s, int pos) {
    vector<vector<string>> result;
    int s_len = s.size();
    vector<string> over_size_result[128];
    for (int i = 0; i < 128; ++i) { over_size_result[i] = vector<string> {}; }
    for (int i = 0; i < s_len; ++i) {
        if (pos >= s.at(i).length()) {
            over_size_result[0].emplace_back(s.at(i));
            continue;
        }
        char curr = s.at(i)[pos];
        over_size_result[curr].emplace_back(s.at(i));
    }
    for (int i = 0; i < 128; ++i) {
        if (over_size_result[i].size() > 0) {
            result.emplace_back(over_size_result[i]);
        } 
    }
    s.clear();
    for (auto i : result) {
        for (auto j : i) {
            s.emplace_back(j);
        }
    }
}

void range_bucket_sort(vector<string>& s, int left, int right, int pos) {
    vector<string> range;
    for (int i = left; i <= right; ++i) { range.emplace_back(s.at(i)); }
    bucket_sort(range, pos);
    for (int i = left; i <= right; ++i) { s.at(i) = range.at(i - left); }
}

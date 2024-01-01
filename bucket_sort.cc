#include "bucket_sort.h"
using namespace std;

// void bucket_sort(vector<string>& s, int pos) {
//     vector<vector<string>> result;
//     int s_len = s.size();
//     vector<string> over_size_result[128];
//     for (int i = 0; i < 128; ++i) { over_size_result[i] = vector<string> {}; }
//     for (int i = 0; i < s_len; ++i) {
//         if (pos >= s.at(i).length()) {
//             over_size_result[0].emplace_back(s.at(i));
//             continue;
//         }
//         char curr = s.at(i)[pos];
//         over_size_result[curr].emplace_back(s.at(i));
//     }
//     for (int i = 0; i < 128; ++i) {
//         if (over_size_result[i].size() > 0) {
//             result.emplace_back(over_size_result[i]);
//         } 
//     }
//     s.clear();
//     for (auto i : result) {
//         for (auto j : i) {
//             s.emplace_back(j);
//         }
//     }
// }

// void range_bucket_sort(vector<string>& s, int left, int right, int pos) {
//     vector<string> range;
//     for (int i = left; i <= right; ++i) { range.emplace_back(s.at(i)); }
//     bucket_sort(range, pos);
//     for (int i = left; i <= right; ++i) { s.at(i) = range.at(i - left); }
// }


// chat
void bucket_sort(vector<string>& s, int pos) {
    vector<string> buckets[128]; // Fixed size array of vectors
    int s_len = s.size();

    // Distribute strings into buckets
    for (int i = 0; i < s_len; ++i) {
        char curr = pos < s[i].length() ? s[i][pos] : 0;
        buckets[curr].emplace_back(move(s[i])); // Use move semantics to avoid copying
    }

    // Combine sorted buckets back into s
    s.clear();
    for (auto& bucket : buckets) {
        for (auto& str : bucket) {
            s.emplace_back(move(str)); // Use move semantics to avoid copying
        }
    }
}

void range_bucket_sort(vector<string>& s, int left, int right, int pos) {
    if (left >= right) return; // No need to sort if range is invalid or has only one element

    vector<string> buckets[128]; // Fixed size array of vectors

    // Distribute strings into buckets
    for (int i = left; i <= right; ++i) {
        char curr = pos < s[i].length() ? s[i][pos] : 0;
        buckets[curr].emplace_back(move(s[i])); // Use move semantics to avoid copying
    }

    // Combine sorted buckets back into s in the specified range
    int index = left;
    for (auto& bucket : buckets) {
        for (auto& str : bucket) {
            s[index++] = move(str); // Use move semantics to avoid copying
        }
    }
}


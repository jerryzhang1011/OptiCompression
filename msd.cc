#include "msd.h"
#include "bucket_sort.h"
using namespace std;

// void range_bucket_sort(std::vector<std::string>& s, int left, int right, int pos);

// void recursive (vector<string>& s, int l, int r, int curr_pos) {
//     if (l >= r) return;
//     range_bucket_sort(s, l, r, curr_pos);
//     int s_len = s.size();
//     int curr_l = l;
//     int curr_r = l + 1;
//     while (curr_r <= r) {
//         if (s.at(curr_r)[curr_pos] != s.at(curr_l)[curr_pos]) {
//             recursive(s, curr_l, curr_r-1, curr_pos + 1);
//             curr_l = curr_r;
//         }
//         curr_r += 1;
//     }
//     recursive(s, curr_l, curr_r-1, curr_pos + 1);
// }

// void msd_radix_sort(vector<string>& s) {
//     recursive (s, 0, s.size() - 1, 0);
//     return;
// }

//chat


// Utility function to get the character at the given index
char charAt(const string& s, int index) {
    if (index < s.length()) return s[index];
    else return 0; // Return null character for index out of bounds
}

void msd_radix_sort_rec(vector<string>& s, int low, int high, int index) {
    if (high <= low) return;

    vector<string> aux(high - low + 1);
    vector<int> count(130, 0); // 129 for character set [0, 128] and 1 for the next index

    // Compute frequency counts
    for (int i = low; i <= high; i++) {
        count[charAt(s[i], index) + 1]++;
    }

    // Transform counts to indices
    for (int r = 0; r < 129; r++) {
        count[r + 1] += count[r];
    }

    // Distribute
    for (int i = low; i <= high; i++) {
        aux[count[charAt(s[i], index)]++] = s[i];
    }

    // Copy back
    for (int i = low; i <= high; i++) {
        s[i] = aux[i - low];
    }

    // Recursively sort for each character value
    for (int r = 0; r < 128; r++) {
        msd_radix_sort_rec(s, low + count[r], low + count[r + 1] - 1, index + 1);
    }
}

void msd_radix_sort(vector<string>& s) {
    msd_radix_sort_rec(s, 0, s.size() - 1, 0);
}


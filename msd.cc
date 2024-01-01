#include "msd.h"
#include "bucket_sort.h"
using namespace std;

void range_bucket_sort(std::vector<std::string>& s, int left, int right, int pos);

void recursive (vector<string>& s, int l, int r, int curr_pos) {
    if (l >= r) return;
    range_bucket_sort(s, l, r, curr_pos);
    int s_len = s.size();
    int curr_l = l;
    int curr_r = l + 1;
    while (curr_r <= r) {
        if (s.at(curr_r)[curr_pos] != s.at(curr_l)[curr_pos]) {
            recursive(s, curr_l, curr_r-1, curr_pos + 1);
            curr_l = curr_r;
        }
        curr_r += 1;
    }
    recursive(s, curr_l, curr_r-1, curr_pos + 1);
}

void msd_radix_sort(vector<string>& s) {
    recursive (s, 0, s.size() - 1, 0);
    return;
}

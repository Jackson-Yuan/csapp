

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;
/**2.80*/
/**
 * 计算3/4x
 * 这题没看懂
 * 先留个答案
 * */
int threefourths(int x) {
    int is_neg = x & INT_MIN;
    int f = x & ~0x3;
    int l = x & 0x3;

    int fd4 = f >> 2;
    int fd4m3 = (fd4 << 1) + fd4;

    int lm3 = (l << 1) + l;
    int bias = (1 << 2) - 1;
    /**is_neg用来判断正负*/
    (is_neg && (lm3 += bias));
    int lm3d4 = lm3 >> 2;

    return fd4m3 + lm3d4;
}
/**2.81*/
/**
 * 生成w-k个1 k个0
 * 生成w-k-j个0 k个1 j个0
 * */
int generateOne(int k) {
    return -1 << k;
}

int generateTwo(int k, int j) {
    int val = -1 << k;
    val = ~val;
    return val << j;
}

/**2.82~2.91 手写*/
int main() {
    cout << INT_MAX * 2;
}

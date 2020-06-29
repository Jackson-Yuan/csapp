

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

/**
 * 2.64
 * */
/**筛选出奇数位的1*/
int any_odd_one(unsigned x) {
    /**
     * 符合条件的32位最终全变为1
     * 因要返回0或1，取反
     * */
    unsigned val = x | 0x55555555;
    return !(~val);
}

/**
 * 2.65
 * */
int old_ones(unsigned x) {
    return x & 1;
}

/**
 * 2.66
 * */
/**从32位中分离出最左边的1*/
int leftmost_one(unsigned x) {
    /**
     * 将x转为0000.....1111111模式
     * 这个操作值得学习
     * 无论x位级表示有多少个1
     * 只看最左边的1
     * 与右移一位后的x做与操作
     * 这时从左边开始至少已有连续2个1
     * 接着再移动2个，变成4个连续1，以此类推，直至最后移动16位
     * 那么从左边开始到末尾就是连续的1
     * */
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    /**
     * 防止x为0
     * */
    return (x >> 1) + (x && 1);
}

/**
 * 2.67
 * */
/**判断在至少为32位的机器是否是32位机器*/
int int_size_is_32() {
    int set_msb = 1 << 31;
    /**之所以不直接1 << 32 是因为c语言的一个规范，移位的位数不能大于等于字长*/
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

/**判断至少为16位的机器是否是32位机器*/
int int_size_is_32_for_16bit() {
    /**同理*/
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

int main() {
    cout << (-1 << 33);
}
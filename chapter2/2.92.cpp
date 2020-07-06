

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;
typedef unsigned float_bits;
/**2.92*/
/**
 * 给定浮点位级表示f，输出-f，若f为NaN，则返回f
 * */
float_bits float_negate(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;

    if (exp == 0xff && frac != 0) return f;
    else return ~sign << 31 | exp << 23 | frac;
}
/**2.93*/
/**
 * 给定浮点位级表示f，输出f的绝对值，若f为NaN，则返回f
 * */
float_bits float_absval(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;
    if (0 == sign) return f;
    else return float_negate(f);
}
/**2.94*/
/**
 * 给定浮点位级表示f，输出2 * f，若f为NaN，则返回f
 * */
float_bits float_twice(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;

    if (exp == 0xff && frac != 0) return f;
    if (exp == 0) frac <<= 1;
    else if (exp == 0xff - 1) {
        exp = 0xff;
        frac = 0;
    } else exp += 1;

    return sign << 31 | exp << 23 | frac;
}
/**2.95*/
/**
 * 给定浮点位级表示f，输出f / 2，若f为NaN，则返回f
 * */
float_bits float_half(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned rest = f & 0x7fffffff;
    unsigned frac = f & 0x7fffff;

    /**必要的舍入处理，为何如此牛逼*/
    unsigned addition = ((frac & 0x3) == 0x3);

    if (exp == 0xff && frac != 0) return f;
    if (exp == 0) {
        /**阶码为0，代表阶码已经无法缩小了，只能动尾数*/
        frac >>= 1;
        frac += addition;
    } else if (exp == 1) {
        /**阶码为1，正好处于规格化与非规格化之间，且此时阶码减一没有任何作用*/
        /**且尾数在非规格化与规格化间少一个加1，所以此时缩小一半，因将尾数右移一位
         * 且置尾数高位为1，正好弥补规格化加1的损失，尾数高位为1，可由阶码是1时右移而来
         * */
        rest >>= 1;
        rest += addition;
        exp = rest >> 23 & 0xff;
        frac = rest & 0x7fffff;
    } else exp -= 1;

    return sign << 31 | exp << 23 | frac;
}
/**2.96*/
/**
 * 给定浮点位级表示f，输出(int)f，若f为NaN，则返回0
 * 溢出返回0x80000000
 * */
int float_f2i(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;
    unsigned bias = 0x7f;

    if (exp == 0xff && frac != 0) return 0;
    /**f小于1*/
    if (exp >= 0 && exp < bias) return 0;
        /**溢出*/
    else if (exp >= 31 + bias) return 0x80000000;
    else {
        int num;
        int e = exp - bias;
        /**规格化 + 1 补上*/
        frac = frac | 0x800000;
        if (e > 23) {
            num = frac << (e - 23);
        } else {
            num = frac >> (23 - e);
        }
        /**根据符号位判断正负*/
        return sign == 1 ? -num : num;
    }
}
/**2.97*/
/**
 * 给定整形i，输出其转为float的格式
 * 考虑舍入
 * */
float_bits i2f(int i) {
    unsigned sign = (unsigned) i >> 31;
    unsigned bias = 0x7f;
    unsigned exp, frac;
    unsigned val;
    if (sign == 1) {
        val = (unsigned) ~i;
        val = val & 0x7fffffff;
        val += 1;
    } else val = (unsigned) i;
    unsigned ite = 32;
    unsigned tmp = val;
    while (ite >= 1 && ((tmp & 0x80000000) != 0x80000000)) {
        tmp <<= 1;
        --ite;
    }
    if (ite == 0) {
        exp = 0;
        frac = 0;
    } else {
        exp = ite - 1 + bias;
        if (ite > 24) {
            /**计算舍入值*/
            int mask = 0x8fffffff;
            mask >>= 56 - ite - 1;
            mask = ~mask;
            unsigned overflow = ((val & mask) == mask);
            val >>= ite - 24;
            val += overflow;
        } else val <<= 24 - ite;
        frac = val & 0x7fffff;
    }

    return sign << 31 | exp << 23 | frac;
}
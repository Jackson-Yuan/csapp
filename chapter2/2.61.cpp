
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

/**
 * 判断算术右移2.62
 * */
bool int_shifts_are_arithmetic() {
    int num = -1;
    return !(num ^ (num >> 1));
}
/** 2.63 */
/**
 * 将已经做完算术右移的结果转为逻辑右移的结果
 * */
unsigned srl(unsigned x, int k) {
    /**
     * 算术右移的结果
     * */
    unsigned xra = (int) x >> k;
    /**
     * 本质上在x为负时因算术右移将多出来的1变为0，其余照旧，利用掩码秒杀之
     * */
    unsigned mask = (unsigned) -1 >> k;
    /**
     * 作与预算即可
     * */
    return xra & mask;
}

/**
 * 将已经做完逻辑右移的结果转为算术右移的结果
 * */
int sra(int x, int k) {
    int xsr1 = (unsigned) x >> k;
    int len = sizeof(int) << 3;
    /**
     * 算出掩码
     * 以为x的正负在右移时补位不同
     * 所以声明辅助变量来判断正负
     * 最后用或的位级运算来得出结果
     * */
    int mask = -1 << (len - k);
    int m = 1 << (len - 1);
    /**
     * 此处否逻辑运算符只会返回0或1
     * 非0视为true无论正负，否则视为false
     * */
    mask &= !(x & m) - 1;
    return xsr1 | (unsigned) mask;

}

int main() {
    int a = -213;
    cout << (sra(a, 4) == a >> 4);
}

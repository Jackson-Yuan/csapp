

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

/**2.68*/
/**
 * n最低有效n位设置为1的掩码
 * */
int lower_one_mask(int n) {
    /**unsigned val = 1;
    val = val << (n - 1);
    val |= val >> 1;
    val |= val >> 2;
    val |= val >> 4;
    val |= val >> 8;
    val |= val >> 16;*/
    /**注释部分代码不具有兼容不同字长机器的特性*/
    unsigned val = 0xffffffff;
    unsigned len = sizeof(int) << 3;
    val = val >> (len - n);

    return (int) val;
}
/**2.69*/
/**
 * 循环移动n位
 * */
unsigned rotate_left(unsigned x, int n) {
    unsigned len = sizeof(int) << 3;
    /**取出因左移n位丢失的位*/
    unsigned remain = x >> (len - n);
    x = x << n;
    return x + remain;
}
/**2.70*/
/**
 * 判断一个数是否可以被n比特的补码形式表示
 * */
int fits_bits(int x, int n) {
    unsigned len = sizeof(int) << 3;
    unsigned offset = len - n;
    return (x << offset >> offset) == x;
}
/**2.71*/
/**
 * 将一个无符号数4个字节
 * 每个字节当成有符号号数
 * 从低到高编号为0~4
 * 现在请提取这四个字节
 * */
int xbyte(unsigned word, int bytenum) {
    unsigned len = sizeof(unsigned);
    unsigned left = (len - 1 - bytenum) << 3, right = (len - 1) << 3;
    /**将第bytenum个字节移至最左边，决定其符号，由于有符号与无符号左移一致放心大胆的移位
     * 然后再将指定字节移至最优端，由于有符号算术移位，符号位保留
     * */
    return (int) word << left >> right;
}
/**2.72 没啥说头，转型问题*/
/**2.73*/
/**
 * 做加法，正溢出返回INT_MAX(本来正溢出应该是负值)，负溢出返回INT_MIN（本来负溢出应该是正值）
 * 此题略玄学
 * 首先确定几个规律：
 * 正溢出只能发生在两个正数上，且就算INT_MAX + INT_MAX 也是个负数，及正溢出只能为负数
 * 同理负溢出只能发生在两个负数上，且负溢出只能为正数
 * condition1 与 condition2 在溢出时都为全1，在非溢出时，必有一个为0，这样就保证不溢出时返回结果为0
 * overflow更像是为了结果硬凑的一个值，暂时就这样吧
 * */
int saturating_add(int x, int y) {
    int sum = x + y;
    unsigned bias = (sizeof(int) << 3) - 1;
    int condition1 = ~(x >> bias ^ y >> bias);
    int resultCharacter = sum >> bias;
    int condition2 = resultCharacter ^x >> bias;
    int remain = INT_MIN;
    int overflow = resultCharacter - remain;
    return overflow & condition1 & condition2;
}
/**2.74*/
/**
 * 检测x - y是否溢出，溢出返回0，否则返回1
 * 与2.73异曲同工
 * */
int tsub_ok(int x, int y) {
    int sum = x - y;
    unsigned bias = (sizeof(int) << 3) - 1;
    int condition1 = x >> bias ^y >> bias;
    int resultCharacter = sum >> bias;
    int condition2 = (resultCharacter ^ x >> bias) | (resultCharacter ^ y >> bias);
    int remain = INT_MIN;
    int overflow = resultCharacter - remain;
    return !(overflow & condition1 & condition2);
}
/**2.75*/
/**
 * 实现有符号数做乘法，取高32位的值
 * 再利用有符号数取高32位的值实现无符号数的高32位
 * 注意是高32位不是低32位，低32位有符号与无符号位级表示是一样的
 * */
int sign_high(int x, int y) {
    int64_t val = (int64_t) x * y;
    return (int) (val >> 32);
}

unsigned unsigned_high(unsigned x, unsigned y) {
    int sig_x = x >> 31;
    int sig_y = y >> 31;
    int sign = sign_high(x, y);
    /**这是个推导式子，利用有符号数与无符号数之间转换而得*/
    return sign + x * sig_y + y * sig_x;
}

unsigned test_unsigned_high(unsigned x, unsigned y) {
    uint64_t val = (uint64_t) x * y;
    return (unsigned) (val >> 32);
}
/**2.76*/
/**
 * 写一个内存分配函数
 * */
void *calloc(size_t nmemb, size_t size) {
    if (nmemb == 0 || size == 0) return NULL;
    unsigned total = nmemb * size;
    void *ans = malloc(total);
    if (ans == NULL) return NULL;
    memset(ans, 0, total);
    return ans;
}/**2.77 乘除操作转换为一些移位操作已取得时间优化（实际上，编译器会自动化替你优化）*/
/**2.78*/
/**
 * 正确的舍入方式计算 x / 2^k(移位方式)
 * 因为c语言的标准是正数向下舍入，负数向上舍入
 * 单纯的移位无法使得负数满足此要求
 * */
int divide_power2(int x, int k) {
    return (x < 0 ? x + (1 << k) - 1 : x) >> k;
}
/**2.79*/
/**
 * 利用移位正确写出3*x/4的操作
 * */
int mul3div4(int x) {
    x = (x << 1) + x;
    return divide_power2(x, 2);
}

int main() {
    cout << (divide_power2(3, 1) == 3 / 2);
}
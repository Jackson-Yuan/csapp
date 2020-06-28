
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;
typedef unsigned char* byte_pointer;
/**
 * 将值转换为字节序列，byte_pointer指针指向最低字节地址
 * 间接表示存储方式为小端法
 * */
void show_bytes(byte_pointer start, size_t len){
    size_t i;
    for (i = 0; i < len; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}
void show_int(int x){
    show_bytes((byte_pointer)&x, sizeof(int));
}
void show_float(float x){
    show_bytes((byte_pointer)&x, sizeof(float));
}
void show_pointer(void *x){
    show_bytes((byte_pointer)&x, sizeof(void*));
}
int main(){
    show_int(328);
}
/**
 * 2.56~2.58一个意思
 * */
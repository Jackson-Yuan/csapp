
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;
typedef unsigned char *byte_pointer;

/**
 * 运用掩码，取出想要的位
 * */
int process(int x, int y) {
    x = x & 0x000000ff;
    y = y & 0xffffff00;
    return x + y;
}

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

int main() {
    int x = process(0x89ABCDEF, 0x76543210);
    show_bytes((byte_pointer) &x, sizeof(int));
}
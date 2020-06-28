
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void replace_byte(unsigned x, int i, unsigned char b) {
    byte_pointer array = (byte_pointer) &x;
    array[i] = b;
    for (size_t i = 0; i < sizeof(unsigned); ++i) {
        printf(" %.2x", array[i]);
    }
    printf("\n");
}

int main() {
    replace_byte(0x12345678, 0, 0xAB);
}
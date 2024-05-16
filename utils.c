#include "utils.h"

void print_string(const char* s) {
    asm volatile( ".option norvc\ncsrrw x0, 0x138, %0\n" : : "r" (s));
}

void print_uint32(uint32_t n) {
    asm volatile( ".option norvc\ncsrrw x0, 0x136, %0\n" : : "r" (n));
}

void print_hex(uint32_t x) {
    asm volatile( ".option norvc\ncsrrw x0, 0x137, %0\n" : : "r" (x));
}

void memcpy(void* dst, const void* src, uint16_t cnt) {
    char *csrc = (char*) src;  
    char *cdst = (char*) dst;
    for(uint32_t i = 0; i < cnt; i++)
        cdst[i] = csrc[i];
}

void readblock(int blkno, void* dst) {
    asm volatile( ".option norvc\ncsrrw x0, 0x400, %0\n" : : "r" (blkno));
    asm volatile( ".option norvc\ncsrrw x0, 0x401, %0\n" : : "r" (dst)); 
}

void fatal(const char* s) {
    print_string(s);
    SYSCON = 0x5555;
}
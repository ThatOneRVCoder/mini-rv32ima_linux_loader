#ifndef UTILS_H
#define UTILS_H

#define uint64_t unsigned long long
#define uint32_t unsigned long
#define uint16_t unsigned int
#define uint8_t unsigned char
#define NULL ((void*) 0)

extern unsigned int SYSCON;

void print_string(const char* s);
void print_uint32(uint32_t n);
void print_hex(uint32_t x);
void memcpy(void* dst, const void* src, uint16_t cnt);
void readblock(int blkno, void* dst);
void fatal(const char* s);

#endif
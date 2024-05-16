#include <stdarg.h>
#include "loader.h"
#include "utils.h"

void entry() {
    print_string("\n\n");
    print_string("RISC-V Linux Loader V1.0.0\n");

    startLinux();

    print_string("\nError! Linux has not been run! Has an error occured?\n");
    SYSCON = 0x5555;
}
#include "d_main.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // Added new function call to be able to compile GUI and CLI
    // at the same time.
    start(argc, argv, 1);
    return 0;
}

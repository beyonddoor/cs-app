#include <stdio.h>
#include <tau/tau.h>
#include "bytes.h"

TAU_MAIN()

TEST(Floats, bytes)
{
    float f = 0;
    show_float_bytes(f);
}
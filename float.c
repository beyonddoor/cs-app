#include <stdio.h>
#include <tau/tau.h>
#include "bytes.h"
#include <math.h>

TAU_MAIN()

TEST(Floats, bytes)
{
    float f = 0;
    show_float_bytes(f);
    show_float_bytes(.0f);
    show_float_bytes(-.0f);

    show_float_bytes(1/.0f);
    show_float_bytes(-1/.0f);
}
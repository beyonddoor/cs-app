#include "bytes.h"
#include <tau/tau.h>

TAU_MAIN()

TEST(demo_float, zero)
{
    float zero = -.0f;
    show_float_bytes(zero);
    show_float_bytes(.0f);
    CHECK(zero == .0f);
}

TEST(demo_float, inf)
{
    float inf = -1 / .0f;
    float pos_inf = 1 / .0f;
    show_float_bytes(inf);
    show_float_bytes(pos_inf);
    CHECK(pos_inf == 1 / .0f);
}

TEST(demo_float, nan)
{
    float pos_inf = 1 / .0f;
    float nan = pos_inf - pos_inf;
    show_float_bytes(nan);
    show_float_bytes(-nan);
    CHECK(nan != nan); // CAUTION
}

void demo_int2float(int int_var)
{
    float float_var = int_var;
    show_float_bytes(float_var);
    printf("0x%x = %d, %f, ", int_var, int_var, float_var);
    show_float_bytes(float_var);
}

TEST(demo_float, int2float)
{
    demo_int2float(0x12347f);
    demo_int2float(0x1234ff);
    demo_int2float(0xffff80);
    demo_int2float(0x12345678);
}

TEST(demo_double, zero)
{
    double zero = -.0;
    show_double_bytes(zero);
    show_double_bytes(.0);
    CHECK(zero == .0);
}

TEST(demo_double, inf)
{
    double inf = -1 / .0;
    double pos_inf = 1 / .0;
    show_double_bytes(inf);
    show_double_bytes(pos_inf);
    CHECK(pos_inf == 1 / .0);
}

TEST(demo_double, nan)
{
    double pos_inf = 1 / .0;
    double nan = pos_inf - pos_inf;
    show_double_bytes(nan);
    show_double_bytes(-nan);
    CHECK(nan != nan); // CAUTION
}

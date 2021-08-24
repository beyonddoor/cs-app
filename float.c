#include "bytes.h"
#include <tau/tau.h>

TAU_MAIN()

TEST(Floats, zero)
{
    float zero = -.0f;
    show_float_bytes(zero);
    show_float_bytes(.0f);
    CHECK(zero == .0f);
}

TEST(Floats, inf)
{
    float inf = -1/.0f;
    float posInf = 1/.0f;
    show_float_bytes(inf);
    show_float_bytes(posInf);
    CHECK(posInf == 1/.0f);
}

TEST(Floats, nan)
{
    float posInf = 1/.0f;
    float nan = posInf - posInf;
    show_float_bytes(nan);
    CHECK(nan != nan);      // CAUTION
}

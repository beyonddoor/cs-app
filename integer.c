#include <stdio.h>
#include <tau/tau.h>

float sum(float array[], unsigned size)
{
    int i = 0;
    float result = 0;
    for (i = 0; i <= size - 1; i++) // BUG!!!
    {
        result += array[i];
    }
    return result;
}

float sum_fixed(float array[], unsigned size)
{
    int i = 0;
    float result = 0;
    for (i = 0; i <= (int)(size - 1); i++) // BUG!!!
    {
        result += array[i];
    }
    return result;
}

int is_str_longer(char* str1, char* str2)
{
    return strlen(str1) - strlen(str2) > 0;  // BUG!!!
}

int is_str_longer_fixed(char* str1, char* str2)
{
    return strlen(str1) > strlen(str2);
}

int is_str_longer_fixed2(char* str1, char* str2)
{
    return (int)(strlen(str1) - strlen(str2))>0;
}

/*
test if addition result of two unsigned ints overflows
*/
int uadd_ok(unsigned x, unsigned y)
{
    unsigned result = x+y;
    return x <= result;
}

/*
test if addtion of two ints not overflow.
BUGGY!!!
*/
int tadd_ok(int x, int y)
{
    int sum = x + y;
    return x == sum - y && y == sum - x;
}

int tadd_ok_fixed(int x, int y)
{
    int sum = x + y;
    if(x >= 0)
    {
        return sum >= y;
    }
    else
    {
        return sum < y;
    }
}

/*
test if subtraction of two ints not overflow.
BUGGY!!!
*/
int tsub_ok(int x, int y)
{
    return tadd_ok_fixed(x, -y);
}

int tsub_ok_fixed(int x, int y)
{
    //TODO
    int sub = x - y;
    if(y >= 0)
    {
        return sub <= x;
    }
    return sub > x;
}

TAU_MAIN()

TEST(UnsignedConversion, sum_fixed)
{
    float array[] = {0, 0, 0, 0, 0, 0, 0, 0};
    float result = sum_fixed(array, 0);
    CHECK(result == 0);
}

TEST(UnsignedConversion, is_str_longer)
{
    CHECK(1 == is_str_longer("abc", "ab"));
    CHECK(1 == is_str_longer("abc", "abcd"));   //BUG!!!
}

TEST(UnsignedConversion, is_str_longer_fixed)
{
    CHECK(1 == is_str_longer_fixed("abc", "ab"));
    CHECK(0 == is_str_longer_fixed("abc", "abcd"));
}

TEST(UnsignedConversion, is_str_longer_fixed2)
{
    CHECK(1 == is_str_longer_fixed2("abc", "ab"));
    CHECK(0 == is_str_longer_fixed2("abc", "abcd"));
}

TEST(UnsignedConversion, convertion)
{
    CHECK((unsigned)-1 == 0xffffffff);
    CHECK((unsigned)-2 == 0xfffffffe);
    CHECK((int)0xffffffff < 0);
    CHECK(0x0fffffff > 0);
}

TEST(UnsignedConversion, uadd_ok)
{
    CHECK(uadd_ok(128, 128));
    CHECK(!uadd_ok(-1, -1));
    CHECK(!uadd_ok(-1, 1));
    CHECK(!uadd_ok(0xffffffff, 1));
}

TEST(UnsignedConversion, tadd_ok)
{
    CHECK(tadd_ok(128, 128));
    CHECK(tadd_ok(-1, -1));
    CHECK(tadd_ok(-1, 1));
    CHECK(tadd_ok((int)0x7fffffff, (int)0x7fffffff));   //BUG!!!
    CHECK(tadd_ok((int)0x80000000, (int)0x80000000));   //BUG!!!
}

TEST(UnsignedConversion, tadd_ok_fixed)
{
    CHECK(tadd_ok_fixed(128, 128));
    CHECK(tadd_ok_fixed(-1, -1));
    CHECK(tadd_ok_fixed(-1, 1));
    CHECK(!tadd_ok_fixed((int)0x7fffffff, (int)0x7fffffff));
    CHECK(!tadd_ok_fixed((int)0x80000000, (int)0x80000000));
    printf("0x80000000 = %d, 0x80000000+0x80000000=%d\n", 0x80000000, 0x80000000+0x80000000);
    printf("-1=%u\n", -1);
}

TEST(UnsignedConversion, tsub_ok)
{
    CHECK(tsub_ok(128, (int)0x80000000));
    CHECK(tsub_ok(-1, -1));
    CHECK(tsub_ok((int)0x7fffffff, (int)0x7fffffff));
    CHECK(!tsub_ok((int)0x80000000, (int)0x80000000));       //BUG!!!
    CHECK((int)-0x80000000 == 0x80000000);
    printf("-0x80000000=%x\n", -0x80000000);
}

TEST(UnsignedConversion, tsub_ok_fixed)
{
    printf("128 - (int)0x80000000 = %x\n", 128 - (int)0x80000000);
    //CHECK(tsub_ok_fixed(128, (int)0x80000000));//!!!
    CHECK(tsub_ok_fixed(-1, -1));
    CHECK(tsub_ok_fixed((int)0x7fffffff, (int)0x7fffffff));
    CHECK(tsub_ok_fixed((int)0x80000000, (int)0x80000000));
}

TEST(UnsignedConversion, implict_truncate)
{
    uint64_t var = 0xffffffffffff0000;
    unsigned intVar = var;
}

TEST(UnsignedConversion, wired_expr)
{
    {
        int x = 0x80000000;
        int result = x - 1;
        CHECK(x<=0);
        printf("%d-1=%d, %d\n", x, x-1, x-1>0);
        CHECK(x<=0 && result>=0);
        //CHECK(x<=0 && x-1>=0);      //!!!
    }

    // x = 0x7;
    // CHECK(x & 7 == 7 && x<<29 >=0);    // always false
    
    {
        int x = 0xffff;
        int result = x*x;
        CHECK(result < 0);
        printf("x*x=%x， %d\n", x*x, x*x);
    }

    {
        int x = 0x80000000;
        int result = -x;
        CHECK(!(x>0) && !(result>=0));
    }

    {
        int x = 0x80000000;
        int result = -x;
        // CHECK(!(x<0) && !(result<=0));   // always false
    }
}

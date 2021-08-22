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
    return strlen(str1) - strlen(str2) > 0;  // BUG!!
}

int is_str_longer_fixed(char* str1, char* str2)
{
    return strlen(str1) > strlen(str2);
}

int is_str_longer_fixed2(char* str1, char* str2)
{
    return (int)(strlen(str1) - strlen(str2))>0;
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
    CHECK(1 == is_str_longer("abc", "abcd"));   //BUG!!
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
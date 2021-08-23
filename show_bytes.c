#include <stdio.h>
#include "bytes.h"

int main()
{
    int varInt = 0x12345678;
    show_int_bytes(varInt);
    show_unsigned_int_bytes((unsigned)varInt);

    show_long_bytes((long)varInt);
    show_unsigned_long_bytes((unsigned long)varInt);

    show_float_bytes((float)varInt);
    show_double_bytes((double)varInt);

    show_pointer_bytes(&varInt);

    return 0;
}
#include <stdio.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer pointer, unsigned size)
{
    for (unsigned i = 0; i < size; i++) 
    {
        printf("%02x ", pointer[i]);
    }
    printf("\n");
}

void show_int_bytes(int value)
{
    show_bytes((byte_pointer)&value, sizeof(int));
}

void show_unsigned_int_bytes(unsigned int value)
{
    show_bytes((byte_pointer)&value, sizeof(unsigned int));
}

void show_long_bytes(long value)
{
    show_bytes((byte_pointer)&value, sizeof(long));
}

void show_unsigned_long_bytes(unsigned long value)
{
    show_bytes((byte_pointer)&value, sizeof(unsigned long));
}

void show_float_bytes(float value)
{
    show_bytes((byte_pointer)&value, sizeof(double));
}

void show_double_bytes(double value)
{
    show_bytes((byte_pointer)&value, sizeof(double));
}

void show_pointer_bytes(void* value)
{
    show_bytes((byte_pointer)&value, sizeof(void*));
}

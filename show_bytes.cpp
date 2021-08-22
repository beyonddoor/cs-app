#include <stdio.h>

typedef unsigned char *byte_pointer;
typedef void *pointer_type;

void show_bytes(byte_pointer pointer, unsigned size)
{
    for (unsigned i = 0; i < size; i++)
    {
        printf("%02x ", pointer[i]);
    }
    printf("\n");
}

template <typename T>
const char *type_name(const T &name);

template <>
const char *type_name(const short &name)
{
    return "short";
}

template <>
const char *type_name(const unsigned short &name)
{
    return "unsigned short";
}

template <>
const char *type_name(const int &name)
{
    return "int";
}

template <>
const char *type_name(const unsigned int &name)
{
    return "unsigned int";
}

template <>
const char *type_name(const long &name)
{
    return "long";
}

template <>
const char *type_name(const unsigned long &name)
{
    return "unsigned long";
}

template <>
const char *type_name(const float &name)
{
    return "float";
}

template <>
const char *type_name(const double &name)
{
    return "double";
}

template <>
const char *type_name(const pointer_type &name)
{
    return "pointer";
}

template <typename T>
void show_value_bytes(T value)
{
    printf("type: %s, ", type_name(value));
    show_bytes((byte_pointer)&value, sizeof(T));
}

void test_signed_ints()
{
    int varInt = 0x12345678;
    show_value_bytes((short)-varInt);
    show_value_bytes((unsigned short)-varInt);
}

void test_number_type()
{
    int varInt = 0x12345678;
    show_value_bytes((short)varInt);
    show_value_bytes((unsigned short)varInt);

    show_value_bytes(varInt);
    show_value_bytes((unsigned)varInt);

    show_value_bytes((long)varInt);
    show_value_bytes((unsigned long)varInt);

    show_value_bytes((float)varInt);
    show_value_bytes((double)varInt);

    show_value_bytes((pointer_type)&varInt);
}

int main()
{
    test_number_type();
    test_signed_ints();
    return 0;
}
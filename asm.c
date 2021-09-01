#include <stdio.h>
#include <tau/tau.h>

TAU_MAIN()

void ams1()
{
    
}

void decode1(long* xp, long* yp, long* zp)
{

}

void decode2(long* xp, long* yp, long* zp)
{
    __asm__(
        "movq (%rdi), %r8\n"        // 1st
        "movq (%rsi), %rcx\n"       // 2nd
        "movq (%rdx), %rax\n"       // 3rd
        "movq %r8, (%rsi)\n"
        "movq %rcx, (%rdx)\n"       // *zp = *yp
        "movq %rax, (%rdi)\n"       // *xp = *zp
        // "retq\n"
    );
}



TEST(asm, ams1)
{
    long x = 0x1111222233334444L;
    long y = 0x2222333344445555L;
    long z = 0x3333444455556666L;
    decode2(&x, &y, &z);
    CHECK(y == 0x1111222233334444L);
    CHECK(z == 0x2222333344445555L);
    CHECK(x == 0x3333444455556666L);
}
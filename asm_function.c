#include <inttypes.h>
#include <stdio.h>

extern void print_long(long l);

/**
 * save y to xp, and return the old value in xp


0000000000000000 _exchange:
       0: 55                           	pushq	%rbp                
       1: 48 89 e5                     	movq	%rsp, %rbp          
       4: 48 8b 07                     	movq	(%rdi), %rax        ; given x at xp, set as return value
       7: 48 89 37                     	movq	%rsi, (%rdi)        ; store y(2nd arg) to xp(1st arg)
       a: 5d                           	popq	%rbp
       b: c3                           	retq
 */
long exchange(long *xp, long y)
{
    long x = *xp;
    *xp = y;
    return x;
}

/**
 *      pushq %rbp
 *      movq %rsp, %rbp
 * 
 *      movq %rdi, %rax
 *      addq %rsi, %rax
 *      
 *      pop %rbp
 *      retq
 * 
 * 
    10: 55                           	pushq	%rbp
      11: 48 89 e5                     	movq	%rsp, %rbp
      14: 48 8d 04 37                  	leaq	(%rdi,%rsi), %rax
      18: 5d                           	popq	%rbp
      19: c3                           	retq
 */
long add(long x, long y)
{
    return x + y;
}

long identity(long x)
{
    return x;
}

/*
      30: 55                            pushq   %rbp
      31: 48 89 e5                      movq    %rsp, %rbp
      34: 41 56                         pushq   %r14            ; callee have to reserve these registers
      36: 53                            pushq   %rbx        
      37: 49 89 f6                      movq    %rsi, %r14      ; save arg2
      3a: e8 00 00 00 00                callq   0 <_add2+0xf>
      3f: 48 89 c3                      movq    %rax, %rbx      ; save result
      42: 4c 89 f7                      movq    %r14, %rdi
      45: e8 00 00 00 00                callq   0 <_add2+0x1a>
      4a: 48 01 d8                      addq    %rbx, %rax
      4d: 5b                            popq    %rbx
      4e: 41 5e                         popq    %r14
      50: 5d                            popq    %rbp
      51: c3                            retq
      52: 66 2e 0f 1f 84 00 00 00 00 00 nopw    %cs:(%rax,%rax)
      5c: 0f 1f 40 00                   nopl    (%rax)
*/
long add2(long x, long y)
{
    long res1 = identity(x);
    long res2 = identity(y);
    return res1 + res2;
}

long uchar_long(unsigned char c)
{
    unsigned char cc = 'a';
    long temp = cc;
    print_long(temp);
    return c;
}

/*
      44: 48 8d 04 bf                   leaq    (%rdi,%rdi,4), %rax
      48: 48 8d 04 70                   leaq    (%rax,%rsi,2), %rax
      4c: 48 8d 04 d0                   leaq    (%rax,%rdx,8), %rax
*/
long demo_lea(long x, long y, long z)
{
    return x + 4 * x + 2 * y + 8 * z;
}

/*
      64: 31 fe                         xorl    %edi, %esi
      66: 48 c1 e2 04                   shlq    $4, %rdx
      6a: 48 8d 04 52                   leaq    (%rdx,%rdx,2), %rax
      6e: 81 e6 0f 0f 0f 0f             andl    $252645135, %esi
      74: 48 29 f0                      subq    %rsi, %rax
*/
long arith(long x, long y, long z)
{
    long tl = x ^ y;
    long t2 = z * 48;
    long t3 = tl & 0x0F0F0F0F;
    long t4 = t2 - t3;
    return t4;
}

typedef unsigned __int128 uint128_t;

/*
      84: 48 89 d0                      movq    %rdx, %rax
      87: 48 f7 e6                      mulq    %rsi
      8a: 48 89 57 08                   movq    %rdx, 8(%rdi)
      8e: 48 89 07                      movq    %rax, (%rdi)
*/
void store_uprod(uint128_t *dest, uint64_t x, u_int64_t y)
{
    *dest = x * (uint128_t)y;
}

/*
      a4: 49 89 d0                      movq    %rdx, %r8
      a7: 48 89 f8                      movq    %rdi, %rax
      aa: 48 99                         cqto    ; signed expansion, %rdx invovled
      ac: 48 f7 fe                      idivq   %rsi
      af: 49 89 00                      movq    %rax, (%r8)
      b2: 48 89 11                      movq    %rdx, (%rcx)
*/
void remdiv(long x, long y, long *qp, long *rp)
{
    long q = x / y;
    long r = x % y;
    *qp = q;
    *rp = r;
}

/*
      c4: 49 89 d0                      movq    %rdx, %r8
      c7: 48 89 f8                      movq    %rdi, %rax
      ca: 31 d2                         xorl    %edx, %edx  ; zero expansion, %rdx invovled
      cc: 48 f7 f6                      divq    %rsi
      cf: 49 89 00                      movq    %rax, (%r8)
      d2: 48 89 11                      movq    %rdx, (%rcx)
*/
void uremdiv(unsigned long x, unsigned long y, unsigned long *qp, unsigned long *rp)
{
    unsigned long q = x / y;
    unsigned long r = x % y;
    *qp = q;
    *rp = r;
}

void getlong(long *res)
{
    *res = 0x12345678L;
}

void args4(char c, int i, long l, char *msg)
{
    long res = 0;
    res += c;
    res += i;
    res += l;
    printf(msg);
}

/*
0000000000000100 _args10:
     100: 55                            pushq   %rbp
     101: 48 89 e5                      movq    %rsp, %rbp
     104: 53                            pushq   %rbx
     105: 4c 8b 55 28                   movq    40(%rbp), %r10
     109: 4c 8b 5d 20                   movq    32(%rbp), %r11
     10d: 48 8b 45 18                   movq    24(%rbp), %rax
     111: 48 8b 5d 10                   movq    16(%rbp), %rbx  ; the return address stored in 8(%rbp), old %rbp stored in 0(%rbp)
     115: c7 07 01 00 00 00             movl    $1, (%rdi)      ; here 6 args stored in register
     11b: c7 06 02 00 00 00             movl    $2, (%rsi)
     121: c7 02 03 00 00 00             movl    $3, (%rdx)
     127: c7 01 04 00 00 00             movl    $4, (%rcx)
     12d: 41 c7 00 05 00 00 00          movl    $5, (%r8)
     134: 41 c7 01 06 00 00 00          movl    $6, (%r9)       
     13b: c7 03 07 00 00 00             movl    $7, (%rbx)      ; 4 args left stored on stack
     141: c7 00 08 00 00 00             movl    $8, (%rax)
     147: 41 c7 03 09 00 00 00          movl    $9, (%r11)
     14e: 41 c7 02 0a 00 00 00          movl    $10, (%r10)
     155: 5b                            popq    %rbx
     156: 5d                            popq    %rbp
     157: c3                            retq
     158: 0f 1f 84 00 00 00 00 00       nopl    (%rax,%rax)
*/
void args10(int *ptr1, int *ptr2, int *ptr3, int *ptr4, int *ptr5, int *ptr6, int *ptr7, int *ptr8, int *ptr9, int *ptr10)
{
    *ptr1 = 1;
    *ptr2 = 2;
    *ptr3 = 3;
    *ptr4 = 4;
    *ptr5 = 5;
    *ptr6 = 6;
    *ptr7 = 7;
    *ptr8 = 8;
    *ptr9 = 9;
    *ptr10 = 10;
}

/*
     160: 55                            pushq   %rbp
     161: 48 89 e5                      movq    %rsp, %rbp
     164: c7 07 01 00 00 00             movl    $1, (%rdi)
     16a: c7 06 02 00 00 00             movl    $2, (%rsi)
     170: c7 02 03 00 00 00             movl    $3, (%rdx)
     176: c7 01 04 00 00 00             movl    $4, (%rcx)
     17c: 41 c7 00 05 00 00 00          movl    $5, (%r8)
     183: 41 c7 01 06 00 00 00          movl    $6, (%r9)
     18a: 48 8b 45 10                   movq    16(%rbp), %rax
     18e: c7 00 07 00 00 00             movl    $7, (%rax)
     194: 48 8b 45 18                   movq    24(%rbp), %rax
     198: c7 00 08 00 00 00             movl    $8, (%rax)
     19e: 48 8b 45 20                   movq    32(%rbp), %rax
     1a2: c7 00 09 00 00 00             movl    $9, (%rax)
     1a8: 48 8b 45 28                   movq    40(%rbp), %rax
     1ac: c7 00 0a 00 00 00             movl    $10, (%rax)
     1b2: 48 8b 45 30                   movq    48(%rbp), %rax
     1b6: c7 00 01 00 00 00             movl    $1, (%rax)
     1bc: 48 8b 45 38                   movq    56(%rbp), %rax
     1c0: c7 00 02 00 00 00             movl    $2, (%rax)
     1c6: 48 8b 45 40                   movq    64(%rbp), %rax
     1ca: c7 00 03 00 00 00             movl    $3, (%rax)
     1d0: 48 8b 45 48                   movq    72(%rbp), %rax
     1d4: c7 00 04 00 00 00             movl    $4, (%rax)
     1da: 48 8b 45 50                   movq    80(%rbp), %rax
     1de: c7 00 05 00 00 00             movl    $5, (%rax)
     1e4: 48 8b 45 58                   movq    88(%rbp), %rax
     1e8: c7 00 06 00 00 00             movl    $6, (%rax)
     1ee: 48 8b 45 60                   movq    96(%rbp), %rax
     1f2: c7 00 07 00 00 00             movl    $7, (%rax)
     1f8: 48 8b 45 68                   movq    104(%rbp), %rax
     1fc: c7 00 08 00 00 00             movl    $8, (%rax)
     202: 48 8b 45 70                   movq    112(%rbp), %rax
     206: c7 00 09 00 00 00             movl    $9, (%rax)
     20c: 48 8b 45 78                   movq    120(%rbp), %rax
     210: c7 00 0a 00 00 00             movl    $10, (%rax)
     216: 5d                            popq    %rbp
     217: c3                            retq
*/
void args20(int *ptr1, int *ptr2, int *ptr3, int *ptr4, int *ptr5, int *ptr6, int *ptr7, int *ptr8, int *ptr9, int *ptr10,
            int *ptr11, int *ptr12, int *ptr13, int *ptr14, int *ptr15, int *ptr16, int *ptr17, int *ptr18, int *ptr19, int *ptr20)
{
    *ptr1 = 1;
    *ptr2 = 2;
    *ptr3 = 3;
    *ptr4 = 4;
    *ptr5 = 5;
    *ptr6 = 6;
    *ptr7 = 7;
    *ptr8 = 8;
    *ptr9 = 9;
    *ptr10 = 10;
    *ptr11 = 1;
    *ptr12 = 2;
    *ptr13 = 3;
    *ptr14 = 4;
    *ptr15 = 5;
    *ptr16 = 6;
    *ptr17 = 7;
    *ptr18 = 8;
    *ptr19 = 9;
    *ptr20 = 10;
}

/*
     220: 55                            pushq   %rbp
     221: 48 89 e5                      movq    %rsp, %rbp
     224: 48 01 3e                      addq    %rdi, (%rsi)
     227: 01 11                         addl    %edx, (%rcx)
     229: 8a 45 10                      movb    16(%rbp), %al
     22c: 66 45 01 01                   addw    %r8w, (%r9)
     230: 48 8b 4d 18                   movq    24(%rbp), %rcx
     234: 00 01                         addb    %al, (%rcx)
     236: 5d                            popq    %rbp
     237: c3                            retq
     238: 0f 1f 84 00 00 00 00 00       nopl    (%rax,%rax)
*/
void arg8(long a1, long *a1p,
          int a2, int *a2p,
          short a3, short *a3p,
          char a4, char *a4p)
{
    *a1p += a1;
    *a2p += a2;
    *a3p += a3;
    *a4p += a4;
}

/*
     240: 55                            pushq   %rbp
     241: 48 89 e5                      movq    %rsp, %rbp
     244: 48 83 ec 10                   subq    $16, %rsp           ; alloc for local vars, 16 bytes
     248: 48 c7 45 f0 00 00 00 00       movq    $0, -16(%rbp)
     250: c7 45 f8 00 00 00 00          movl    $0, -8(%rbp)
     257: 66 c7 45 fc 00 00             movw    $0, -4(%rbp)
     25d: c6 45 ff 00                   movb    $0, -1(%rbp)
     261: 48 8d 45 ff                   leaq    -1(%rbp), %rax      
     265: 48 8d 75 f0                   leaq    -16(%rbp), %rsi     ; arg2
     269: 48 8d 4d f8                   leaq    -8(%rbp), %rcx      ; arg 4
     26d: 4c 8d 4d fc                   leaq    -4(%rbp), %r9       ; arg 6
     271: bf 34 12 00 00                movl    $4660, %edi         ; arg 1
     276: ba 45 00 00 00                movl    $69, %edx           ; arg 3
     27b: 41 b8 67 00 00 00             movl    $103, %r8d          ; arg 5
     281: 50                            pushq   %rax                ; arg 8, the last arg
     282: 6a 89                         pushq   $-119               ; arg 7
     284: e8 00 00 00 00                callq   0 <_call_arg8+0x49>
     289: 48 83 c4 20                   addq    $32, %rsp
     28d: 5d                            popq    %rbp
     28e: c3                            retq
*/
void call_arg8()
{
    long var_long = 0;
    int var_int = 0;
    short var_short = 0;
    char var_char = 0;
    arg8(0x1234L, &var_long, 0x45, &var_int, 0x67, &var_short, 0x89, &var_char);
}

/*
also 16 bytes temp vars
*/
void call_arg8_2()
{
    char var_char = 0;
    int var_int = 0;
    long var_long = 0;
    short var_short = 0;
    arg8(0x1234L, &var_long, 0x45, &var_int, 0x67, &var_short, 0x89, &var_char);
}

/*
     320: 55                            pushq   %rbp
     321: 48 89 e5                      movq    %rsp, %rbp
     324: b8 01 00 00 00                movl    $1, %eax
     329: 48 83 ff 02                   cmpq    $2, %rdi
     32d: 7c 1f                         jl      31 <_rfact+0x2e>
     32f: b8 01 00 00 00                movl    $1, %eax
     334: 66 2e 0f 1f 84 00 00 00 00 00 nopw    %cs:(%rax,%rax)
     33e: 66 90                         nop
     340: 48 0f af c7                   imulq   %rdi, %rax
     344: 48 83 ff 02                   cmpq    $2, %rdi
     348: 48 8d 7f ff                   leaq    -1(%rdi), %rdi
     34c: 7f f2                         jg      -14 <_rfact+0x20>
     34e: 5d                            popq    %rbp
     34f: c3                            retq
*/
long rfact(long n)
{
    long result;
    if (n <= 1)
    {
        result = 1;
    }
    else
    {
        result = n * rfact(n - 1);
    }
    return result;
}

long demo_array()
{
    int ints[10] = {0,1,2,3,4,5,6,7};       //10*4
    char chars[] = "hello world";
    long longs[10];                         //10*8
    long sum = 0;
    for (int i = 0; i < 10; i++)
    {
        sum += ints[i];
        sum += longs[i];
        sum += chars[i];
    }

    return sum;
}

/*
NOTE: supported by c99
*/
int var_ele(int n, int A[n][n], long i, long j)
{
    return A[i][j];
}

struct prob
{
    int *p;
    struct {
        int x,y;
    } s;
    struct prob *next;
};

int dump_prob(struct prob *ptr)
{
    int result = 0;
    result += *ptr->p;
    result += ptr->s.x;
    result += *ptr->next->p;
    return result;
}


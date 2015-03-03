#include <htc.h>
 
#define WE_HIGH \
    P0 = P0 | 0x1;
 
#define WE_LOW \
    P0 = P0 & (~0x1);
 
#define OE_HIGH \
    P0 = P0 | 0x2;
 
#define OE_LOW \
    P0 = P0 & (~0x2);
 
#define CS_HIGH \
    P0 = P0 | 0x8;
 
#define CS_LOW \
    P0 = P0 & (~0x8);
 
#define GATE_HIGH \
    P0 = P0 | 0x4;
 
#define GATE_LOW \
    P0 = P0 & (~0x4);
 
#define ADDR P2
#define RAM0 P1
#define RAM1 P3
 
#define r0 0
#define r1 1
#define r2 2
#define r3 3
 
                  //  eq in su
#define ADD  0x00 //   0  0  0
#define SUB  0x01 //   0  0  1
#define ADDI 0x02 //   0  1  0
#define SUBI 0x03 //   0  1  1
#define BGT  0x04 //   1  0  0
#define BEQ  0x05 //   1  0  1
#define BGTI 0x06 //   1  1  0
#define BEQI 0x07 //   1  1  1
 
#define ASM(addr, cmd, o1, o2, o3)      \
    ADDR = addr;                        \
    RAM1 = o1 | (o2 << 2) | (cmd << 4); \
    RAM0 = o3;                          \
    WE_LOW;                             \
    WE_HIGH 
 
int main()
{
    int i;
    GATE_LOW;
    OE_HIGH;
    CS_LOW;
     
#define LOOP 4
#define EXIT 8
 
    ASM(0, ADD, r1, r0, r0);
    ASM(1, ADD, r1, r0, r0);
    ASM(2, ADDI, r2, r0, ~1);
    ASM(3, ADDI, r3, r0, ~20);
 
    ASM(4, ADD, r1, r1, r2);     // loop begin
    ASM(5, ADDI, r2, r2, ~1); 
    ASM(6, BEQI, r2, r3, EXIT); 
    ASM(7, BEQI, r0, r0, LOOP);  // loop end
 
    ASM(8, BEQI, r1, r1, EXIT);  // infinite loop
 
    for (i = 0; i < 20; i ++);   // discharge
    GATE_HIGH;
    OE_LOW;
    while (1);
    return 0;
}

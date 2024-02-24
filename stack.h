#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;

#define STACK_SIZE 16

extern u16 stack[STACK_SIZE];
extern u8 sp;

bool pushS(u16 value);
u16 popS();

#include "stack.h"

u16 stack[16];
u8 sp;

bool pushS(u16 value) {
    if (sp < 16) {
        stack[++sp] = value;
        return true;
    } else {
        return false;
    }
}

u16 popS() {
    if (sp == 0) {
        return 0;
    } else {
        return stack[sp--];
    }
}

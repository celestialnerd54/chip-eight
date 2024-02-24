#include <stdbool.h>
#include <stdint.h>

#define MEMSIZE 4096

extern uint8_t memory[MEMSIZE];
extern uint16_t pc;
extern uint16_t I;
extern uint8_t V[16];
extern uint8_t vf;

bool rom_load(const char *filename);
uint16_t opcode();
void cycle();

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "stack.h"
#include "display.h"

#define MEMSIZE 4096

uint8_t memory[MEMSIZE];
uint16_t pc = 0x200;
uint16_t I = 0;
uint8_t V[16];

bool rom_load(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return false;
    }
    int byte;
    int i = 0;
    while ((byte = fgetc(file)) != EOF) {
        memory[pc+i] = byte;
        i++;
    }
    fclose(file);
    return true;
}

u16 opcode() {
    return memory[pc] << 8 | memory[pc+1];
}

void execute(u16 opcode);

void cycle(char *romfile) {
    rom_load(romfile);
    while (1) {
        execute(opcode());
        pc += 2;
        updateDisplay();
        usleep(10000);
    }
}

void execute(u16 opcode) {
    u8 x = (opcode >> 8) & 0x0F;
    u8 y = (opcode >> 4) & 0x0F;
    u8 n = opcode & 0x0F;
    u8 nn = opcode & 0xFF;
    u16 nnn = opcode & 0xFFF;

    switch (opcode & 0xf000) {
        case 0x0000:
            if (opcode == 0x00e0) {
                clearDisplay();
            } else if (opcode == 0x00ee) {
                pc = popS();
            }
            break;

        case 0x1000:
            pc = nnn - 2;
            break;

        case 0x2000:
            pushS(pc);
            pc = nnn;
            break;

        case 0x3000:
            if (V[x] == nn) {
                pc += 2;
            }
            break;

        case 0x4000:
            if (V[x] != nn) {
                pc += 2;
            }
            break;

        case 0x5000:
            if (V[x] == V[y]) {
                pc += 2;
            }
            break;

        case 0x9000:
            if (V[x] != V[y]) {
                pc += 2;
            }
            break;

        case 0x6000:
            V[x] = nn;
            break;

        case 0x7000:
            V[x] += nn;
            break;

        case 0x8000:
            switch (n) {
                case 0:
                    V[x] = V[y];
                    break;
                case 1:
                    V[x] |= V[y];
                    break;
                case 2:
                    V[x] &= V[y];
                    break;
                case 3:
                    V[x] ^= V[y];
                    break;
                case 4:
                    V[x] += V[y];
                    break;
                case 5:
                    V[x] -= V[y];
                    break;
                case 7:
                    V[x] = V[y] - V[x];
                    break;
                case 6:
                    V[x] = V[y];
                    V[0xf] = V[x] & 0x01;
                    V[x] >>= 1;
                    break;
                case 0xe:
                    V[x] = V[y];
                    V[0xf] = (V[x] & 0x80) >> 7;
                    V[x] <<= 1;
                    break;
            }
            break;

        case 0xA000:
            I = nnn;
            break;

        case 0xB000:
            pc = nnn + V[x];

        case 0xd000:
            V[0xf] = 0;
            uint8_t i, j;

            for (i= 0; i < n; i++) {
                uint8_t sprite = memory[I + i];
                for (j = 0; j < 8; j++) {
                    if ((sprite & 0x80) > 0) {
                        if (pixelDisplay(V[x]+j, V[y]+i)) {
                            V[0xf] = 1;
                        }
                    }
                    sprite <<= 1;
                }
            }
    }
}

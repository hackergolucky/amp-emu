/*  Amp - A GBA emulator written in C/C++
 *  Copyright (C) 2021 hackergolucky (Avery Ramsey)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __ARM7TDMI_H__
#define __ARM7TDMI_H__

#include <stdbool.h>
#include <stdint.h>
typedef uint32_t reg32;

enum State {
    STATE_ARM,
    STATE_THUMB
};

enum Mode {
    MODE_USR    = 0b10000,
    MODE_FIQ    = 0b10001,
    MODE_IRQ    = 0b10010,
    MODE_SVC    = 0b10011,
    MODE_ABT    = 0b10111,
    MODE_UND    = 0b11011,
    MODE_SYS    = 0b11111
};
int mode_to_index(enum Mode mode);


struct arm7tdmi_t
{
    bool running;

    enum State state;
    // These registers hide under the hood.
    // They are not accessed directly.
    reg32 _regs[13];
    reg32 _hiRegs_fiq[5];
    reg32 _sp[6];
    reg32 _lr[6];
    reg32 _pc;

    union cpsr_u
    {
        uint32_t word;

        struct
        {
            uint8_t mode : 5;
            bool t : 1;
            bool f : 1;
            bool i : 1;
            uint32_t u : 20;
            bool v : 1;
            bool c : 1;
            bool z : 1;
            bool n : 1;
        };
    } _spsr[5];

    // These are the registers that
    // are actually used by the program
    reg32 *regs[7][16];
    union cpsr_u cpsr;
    union cpsr_u *spsr[7];
};

void arm7tdmi_initRegs(struct arm7tdmi_t *arm7tdmi);
void arm7tdmi_init(struct arm7tdmi_t *arm7tdmi);
void arm7tdmi_destroy(struct arm7tdmi_t *arm7tdmi);

#endif // __ARM7TDMI_H__

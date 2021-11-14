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

#include "arm7tdmi.h"

#include <stdio.h>
#include <stddef.h>


/*
 * This function converts a mode name
 * into an index for the mode array
 */
int mode_to_index(enum Mode mode)
{
    switch(mode) {
        case MODE_USR: // 0b10000
            return 0;
        case MODE_FIQ:  // 0b10001
            return 1;
        case MODE_IRQ:  // 0b10010
            return 2;
        case MODE_SVC:  // 0b10011
            return 3;
        case MODE_ABT:  // 0b10111
            return 4;
        case MODE_UND:  // 0b11011
            return 5;
        case MODE_SYS:  // 0b11111
            return 6;
        
        default:
            printf("Attempting to convert mode that doesn't exist! Using MODE_USR instead.\n");
            return 0; // default to USR mode
    }
}

void arm7tdmi_initRegs(struct arm7tdmi_t *arm7tdmi)
{
    // Set the regs for each mode
    for(int m = 0; m < 7; m++) {
        for(int r = 0; r < 13; r++) {
            arm7tdmi->regs[m][r] = &arm7tdmi->_regs[r];
        }
    }
    // Then replace the FIQ high regs
    for(int r = 8; r < 13; r++) {
        arm7tdmi->regs[mode_to_index(MODE_FIQ)][r] = &arm7tdmi->_hiRegs_fiq[r - 8];
    }
    // Next, set each mode's SP, LR, and PC
    for(int m = 0; m < 7; m++) {
        int index = m;
        // if this is SYS, use USR's registers
        if(m == 6) {
            index = 0;
        }
        arm7tdmi->regs[m][13] = &arm7tdmi->_sp[index];
        arm7tdmi->regs[m][14] = &arm7tdmi->_lr[index];
        arm7tdmi->regs[m][15] = &arm7tdmi->_pc;
    }
    // Finally, set the SPSRs
    for(int m = 1; m < 6; m++) {
        arm7tdmi->spsr[m] = &arm7tdmi->_spsr[m - 1];
    }
    // No spsr for USR or SYS modes
    arm7tdmi->spsr[0] = arm7tdmi->spsr[6] = NULL;
}

void arm7tdmi_init(struct arm7tdmi_t *arm7tdmi)
{
    arm7tdmi_initRegs(arm7tdmi);
}

void arm7tdmi_destroy(struct arm7tdmi_t *arm7tdmi)
{

}

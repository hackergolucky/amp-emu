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

#include <stdlib.h>

#include "gba.h"
#include "arm7tdmi.h"


int gba_init(struct gba_t *gba)
{
    gba->running = true;

    gba->arm7tdmi = (struct arm7tdmi_t *) malloc(sizeof(struct arm7tdmi_t));
    arm7tdmi_init(gba->arm7tdmi);

    return 0;
}

void gba_destroy(struct gba_t *gba)
{
    if(gba->arm7tdmi) {
        arm7tdmi_destroy(gba->arm7tdmi);
        free(gba->arm7tdmi);
    }
}

void gba_update(struct gba_t *gba)
{
    
}

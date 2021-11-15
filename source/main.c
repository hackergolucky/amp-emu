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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "window.h"
#include "gba.h"


int main(int argc, char *argv[])
{
    int retval = 0;

    struct window_t *win = (struct window_t *) malloc(sizeof(struct window_t));
    struct gba_t *gba = (struct gba_t *) malloc(sizeof(struct gba_t));
    bool init_failed =
        window_init(win, 240, 160) | 
        gba_init(gba);

    if(init_failed) {
        retval = 1;
        goto destroy;
    }

    while(win->running && gba->running)
    {
        window_update(win);
        gba_update(gba);
    }

    destroy:
        window_destroy(win);
        gba_destroy(gba);

        free(win);
        free(gba);
        
        return retval;
}

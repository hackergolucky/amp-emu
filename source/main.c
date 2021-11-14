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

#include "gba.h"


int main(int argc, char *argv[])
{
    int retval = 0;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow(
        "Amp GBA Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    if(!window)
    {
        retval = 1;
        goto end;
    }

    struct gba_t *gba = (struct gba_t *) malloc(sizeof(struct gba_t));
    gba_init(gba);

    while(true)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                goto destroy;
        }
    }

    destroy:
        SDL_DestroyWindow(window);
        gba_destroy(gba);
    end:
        SDL_Quit();
        return retval;
}

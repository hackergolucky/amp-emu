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
#include "window.h"
#include <SDL2/SDL.h>


int window_init(struct window_t *win)
{
    win->running = true;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    if((win->window = SDL_CreateWindow(
        "Amp GBA Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    )) == NULL)
    {
        printf("Error creating SDL_Window instance!\n");
        return 1;
    }

    return 0;
}

void window_destroy(struct window_t *win)
{
    if(win->window)
        SDL_DestroyWindow(win->window);
    SDL_Quit();
}

void window_update(struct window_t *win)
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT) {
            win->running = false;
        }
    }
}

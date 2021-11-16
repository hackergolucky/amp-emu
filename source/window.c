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


void window_create(struct window_t *win, const char *title, int w, int h)
{
    win->sdl_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w,
        h,
        SDL_WINDOW_HIDDEN | SDL_WINDOW_SKIP_TASKBAR
    );

    win->winID = SDL_GetWindowID(win->sdl_window);

    win->sdl_renderer = SDL_CreateRenderer(
        win->sdl_window,
        -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
    );
}

void window_show(struct window_t *win)
{
    win->isShown = true;
    SDL_ShowWindow(win->sdl_window);
}

void window_close(struct window_t *win)
{
    win->isShown = false;
    SDL_HideWindow(win->sdl_window);
}

void window_destroy(struct window_t *win)
{
    SDL_DestroyRenderer(win->sdl_renderer);
    SDL_DestroyWindow(win->sdl_window);
}

struct window_t * typeToWindow(struct windowmgr_t *mgr, enum WindowType type)
{
    switch(type)
    {
        case WINDOW_GAME:
            return mgr->gameWindow;
        case WINDOW_TEST:
            return mgr->testWindow;
        default:
            printf("Error! Attempting to fetch window type %d, which doesn't exist!\n", type);
            return NULL;
    }
}

void windowmgr_init(struct windowmgr_t *mgr)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    mgr->gameWindow = (struct window_t *) malloc(sizeof(struct window_t));
    window_create(mgr->gameWindow, "Amp GBA Emulator", 240, 160);

    mgr->anyWindowsRunning = true;
}

void windowmgr_destroy(struct windowmgr_t *mgr)
{
    window_destroy(mgr->gameWindow);
    //window_destroy(mgr->testWindow);

    SDL_Quit();
}

void windowmgr_update(struct windowmgr_t *mgr)
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            mgr->anyWindowsRunning = false;
        }
    }
}

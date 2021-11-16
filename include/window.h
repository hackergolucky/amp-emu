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
#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <stdbool.h>
#include <SDL2/SDL.h>

enum WindowType
{
    WINDOW_GAME,
    WINDOW_TEST,
    WINDOW_COUNT
};

struct window_t
{
    int winID;
    bool isShown;
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
};

void window_create(struct window_t *win, const char *title, int w, int h);
void window_show(struct window_t *win);
void window_close(struct window_t *win);
void window_destroy(struct window_t *win);

struct windowmgr_t
{
    bool anyWindowsRunning;
    
    struct window_t *gameWindow;
    struct window_t *testWindow;
};

struct window_t * typeToWindow(struct windowmgr_t *mgr, enum WindowType type);
void windowmgr_init(struct windowmgr_t *mgr);
void windowmgr_destroy(struct windowmgr_t *mgr);
void windowmgr_update(struct windowmgr_t *mgr);

#endif // __WINDOW_H__

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

#include <SDL2/SDL.h>
#include <stdbool.h>


struct window_t
{
    int width, height, scale;
    uint32_t *pixelbuf;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    bool running;
};

#if __cplusplus
extern "C" {
#endif // __cplusplus

int window_init(struct window_t *win, int width, int height);
void window_destroy(struct window_t *win);

void window_update(struct window_t *win);

#if __cplusplus
}
#endif // __cplusplus

#endif // __WINDOW_H__
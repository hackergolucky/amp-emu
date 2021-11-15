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
#include "nfd.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include <SDL2/SDL.h>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error Requires SDL 2.0.17! Aborting!
#endif


int window_init(struct window_t *win, int width, int height)
{
    win->running = true;
    win->width = width;
    win->height = height;
    win->scale = 1;
    win->pixelbuf = (uint32_t *) malloc(win->width * win->height);

    NFD_Init();

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

    if((win->renderer = SDL_CreateRenderer(
        win->window,
        -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
    )) == NULL)
    {
        printf("Error creating SDL_Renderer! %s\n", SDL_GetError());
        return 1;
    }

    if((win->texture = SDL_CreateTexture(
        win->renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        win->width,
        win->height
    )) == NULL)
    {
        printf("Error creating render texture! %s\n", SDL_GetError());
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsClassic();

    ImGui_ImplSDL2_InitForSDLRenderer(win->window);
    ImGui_ImplSDLRenderer_Init(win->renderer);

    return 0;
}

void window_destroy(struct window_t *win)
{
    NFD_Quit();

    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    if(win->pixelbuf)
        free(win->pixelbuf);

    if(win->texture)
        SDL_DestroyTexture(win->texture);
    if(win->renderer)
        SDL_DestroyRenderer(win->renderer);
    if(win->window)
        SDL_DestroyWindow(win->window);
    SDL_Quit();
}

void window_update(struct window_t *win)
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        ImGui_ImplSDL2_ProcessEvent(&e);
        if(e.type == SDL_QUIT ||
            (e.type == SDL_WINDOWEVENT &&
            e.window.event == SDL_WINDOWEVENT_CLOSE &&
            e.window.windowID == SDL_GetWindowID(win->window))
        ) {
            win->running = false;
        }
    }

    for(int i = 0; i < win->width * win->height * win->scale * win->scale; i++) {
        win->pixelbuf[i] = 0xFF0000FF;
    }

    // Begin frame
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame(win->window);
    ImGui::NewFrame();

    // Draw UI
    if(ImGui::BeginMainMenuBar()) {
        if(ImGui::BeginMenu("File")) {
            if(ImGui::MenuItem("Open ROM (.gba)")) {
                nfdchar_t *outPath;
                nfdfilteritem_t filterItem = {"GBA Roms", "gba"};
                nfdresult_t res = NFD_OpenDialog(&outPath, &filterItem, 1, NULL);
                if(res == NFD_OKAY) {
                    printf("Opened GBA Rom: %s\n", (char *) outPath);
                    NFD_FreePath(outPath);
                } else if(res == NFD_CANCEL) {
                    printf("Cancelled opening ROM!\n");
                } else {
                    printf("Error opening file! %s\n", NFD_GetError());
                    win->running = false;
                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Render UI
    ImGui::Render();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    SDL_SetRenderDrawColor(
        win->renderer,
        (Uint8)(clear_color.x * 255),
        (Uint8)(clear_color.y * 255),
        (Uint8)(clear_color.z * 255),
        (Uint8)(clear_color.w * 255)
    );

    // Render game window
    SDL_RenderClear(win->renderer);
    int pitch;
    uint32_t *frontbuf;
    SDL_Rect rect = {0, 0, win->width * win->scale, win->height * win->scale};

    SDL_LockTexture(win->texture, NULL, (void **) &frontbuf, &pitch);
    memcpy((void *) frontbuf, (void *) win->pixelbuf, win->width * win->height * sizeof(uint32_t));
    SDL_UnlockTexture(win->texture);
    SDL_RenderCopy(win->renderer, win->texture, NULL, &rect);

    // Update the frame
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(win->renderer);
}

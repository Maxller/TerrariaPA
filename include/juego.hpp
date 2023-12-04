#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <personaje.hpp>

class Juego
{
private:
    bool isRunning;

    SDL_Window *window;
    SDL_Renderer *renderer;
    Personaje *jugador;
    int seg;

    void InitSDL()
    {
        auto isInitialized = SDL_Init(SDL_INIT_VIDEO) >= 0;
        if (!isInitialized)
        {
            throw SDL_Exception(SDL_GetError());
        }
    }
    void CreateWindowAndRender()
    {
        SDL_CreateWindowAndRenderer(512, 512, SDL_WINDOW_SHOWN, &window, &renderer);

        if (window == NULL || renderer == NULL)
        {
            throw SDL_Exception(SDL_GetError());
        }
    }

public:
    Juego(/* args */) {}

    void Init()
    {
        InitSDL();
        CreateWindowAndRender();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        jugador = new Personaje(renderer);
        seg = 0;

        isRunning = true;
    }

    void HandleEvents()
    {
        SDL_Event event;

        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }
    }

    void Update()
    {
        seg ++;
        jugador->caminar(int(seg/143));
    }

    void Render()
    {
        SDL_RenderClear(renderer);

        SDL_RenderCopyEx(renderer, jugador->getAparencia() , jugador->getSrcRect(), jugador->getDestRect(), 0, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(renderer);
    }

    void Release()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool IsRunning()
    {
        return isRunning;
    }

    ~Juego() {}
};

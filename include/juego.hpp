#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <personaje.hpp>
#include <./input/keyboard.hpp>
#include <./input/imputHandler.hpp>

const int JUMP = 0;
const int LEFT = 1;
const int RIGHT = 2;
Keyboard *keyboard;

class Juego
{
private:
    bool isRunning;

    InputHandler* inputHandler;
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
        
        inputHandler = new InputHandler();
        keyboard = new Keyboard();
        //auto button1 = InputButton{JUMP, SDLK_d};
        auto button1 = InputButton{RIGHT, SDLK_d};
        auto button2 = InputButton{LEFT, SDLK_a};
        keyboard->AddButtonMap(button1);
        keyboard->AddButtonMap(button2);
        inputHandler->AddController(keyboard);
        
        seg = 0;

        isRunning = true;
    }

    void HandleEvents()
    {
        SDL_Event event;
        inputHandler->PreHandleEvent();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            } else {
                inputHandler->HandleEvent(&event);
            }
        }
    }

    void Update()
    {   
            if (keyboard->GetButtonDown(RIGHT)) {
                seg ++;
                jugador->caminar(int(seg/2),SDL_FLIP_NONE);
            }
            if (keyboard->GetButtonUp(RIGHT)) {
                seg = 0;
                jugador->inmovil(SDL_FLIP_NONE);
            }
            if (keyboard->GetButtonDown(LEFT)) {
                seg ++;
                jugador->caminar(int(seg/2),SDL_FLIP_HORIZONTAL);
            }
            if (keyboard->GetButtonUp(LEFT)) {
                seg = 0;
                jugador->inmovil(SDL_FLIP_HORIZONTAL);
            }
        
    }

    void Render()
    {
        SDL_RenderClear(renderer);

        SDL_RenderCopyEx(renderer, jugador->getAparencia() , jugador->getSrcRect(), jugador->getDestRect(), 0, NULL, jugador->getDireccion());

        SDL_RenderPresent(renderer);
    }

    void Release()
    {
        delete inputHandler;
        delete jugador;
        delete keyboard;
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

#pragma once
#include <juego.hpp>
#include <SDL.h>
#include <stdio.h>
#include <exception>
#include <iostream>
#include <chrono>



int main(int argv, char** args)
{
    Juego juego = Juego();
    try{
        juego.Init();
        auto start = std::chrono::system_clock::now();
        while (juego.IsRunning())
        {
            auto current = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsedSeconds = current - start;
            
            juego.HandleEvents();

            juego.Update();

            juego.Render();
            start = current;
        
        }

        juego.Release();
    }
    catch (std::exception &exception)
    {
        fprintf(stderr, exception.what());
        SDL_Quit();
        return -1;
    }
    return 0; 
}

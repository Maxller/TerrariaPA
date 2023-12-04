#pragma once
#include <apariencia.hpp>
#include <SDL.h>

class Character
{
protected:
    Apariencia* apariencia;
    int vida;
    SDL_Rect destRect;
    
public:
    Character(/* args */){}
    
    virtual void caminar(int frame) = 0;
    virtual void saltar() = 0;
    virtual void caer() = 0;
    virtual void accionActiva() = 0;
    ~Character(){}
};
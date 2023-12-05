#pragma once
#include <apariencia.hpp>
#include <character.hpp>
#include <SDL.h>

class Personaje : public Character
{
private:
    int posX, posY, vel, mov;
    SDL_RendererFlip direccion;
    SDL_Renderer *renderer;

public:
    Personaje(SDL_Renderer *renderer)
    {
        this->renderer = renderer;
        apariencia = new Apariencia();
        apariencia->setApariencia("assets/texture/Personaje/PersonajeTerraria.png", renderer, 0, 0);
        posX = 0;
        posY = 0;
        destRect.x = posX;
        destRect.y = posY;
        mov = 0;
        direccion = SDL_FLIP_NONE;
    }
    void inmovil(SDL_RendererFlip direccion)
    {
        apariencia->setApariencia("assets/texture/Personaje/PersonajeTerraria.png", renderer, 0, 0);
        destRect.x = posX;
        destRect.y = posY;
        destRect.h = 100;
        destRect.w = 66;
        this->direccion = direccion;
        mov = 0;
    }
    void caminar(int frame, SDL_RendererFlip direccion) override
    {
        if (mov == frame){
            if(direccion == SDL_FLIP_NONE) posX += 3;
            else posX -= 3;
            mov++;
        }
        frame = (frame % 7);
        apariencia->setApariencia("assets/texture/Personaje/PersonajeTerrariaCaminandoSpriteSheet.png", renderer, frame * 68, 0);
        destRect.x = posX;
        destRect.y = posY;
        destRect.h = 100;
        destRect.w = 68;
        this->direccion = direccion;
    }
    void saltar() override
    {
    }
    void caer() override
    {
    }
    void accionActiva() override
    {
    }
    SDL_Texture *getAparencia()
    {
        return apariencia->getApariencia();
    }

    SDL_Rect *getSrcRect()
    {
        return apariencia->getRect();
    }

    SDL_Rect *getDestRect()
    {
        return &destRect;
    }

    SDL_RendererFlip getDireccion()
    {
        return direccion;
    }

    ~Personaje() {}
};

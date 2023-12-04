#pragma once
#include <exception.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

//la clase parece inecesaria, pero se pude notar que en el juego original de terraria
//la aparencia de los caracteres son diferentes a, pero ya veremos como esta este pedo

class Apariencia
{
private:
    SDL_Rect surceRect; 
    SDL_Texture *texture;
public:

    Apariencia() {
        surceRect.y = 0;
        surceRect.x = 0;
    }

    setApariencia(char *rutaApariencia, SDL_Renderer *renderer, int srcx, int srcy)
    {
        SDL_Surface *surface = IMG_Load(rutaApariencia);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_QueryTexture(texture, NULL, NULL, NULL, &surceRect.h);
        surceRect.w = 68;
        surceRect.y = srcy;
        surceRect.x = srcx;
        SDL_FreeSurface(surface);
    }

    SDL_Texture* getApariencia(){
        return texture;
    }
    
    SDL_Rect* getRect(){
        return &surceRect;
    }

    ~Apariencia() {}
};

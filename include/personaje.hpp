#pragma once
#include <apariencia.hpp>
#include <character.hpp>
#include <SDL.h>

class Personaje : public Character
{
private:
    int posX, posY, vel, mov;
    SDL_Renderer *renderer;

public:
    Personaje(SDL_Renderer *renderer){
        this -> renderer = renderer;
        apariencia = new Apariencia();
        apariencia->setApariencia("assets/texture/Personaje/PersonajeTerraria.png",renderer,0,0);
        posX = 0;
        posY = 0;
        destRect.x=posX;
        destRect.y = posY;
        mov = 0;
    }
    void inmovil(){
        apariencia->setApariencia("assets/texture/Personaje/PersonajeTerraria.png",renderer,0,0);
    }
    void caminar(int frame) override{
        frame = (frame % 7);
        apariencia->setApariencia("assets/texture/Personaje/PersonajeTerrariaCaminandoSpriteSheet.png",renderer,frame * 68, 0);
        if(mov == frame){
            posX += 5;
            mov++;
        }
        destRect.x = posX;
        destRect.y = posY;
        destRect.h = 100;
        destRect.w = 68;

    }
    void saltar() override{

    }
    void caer() override{

    }
    void accionActiva() override{

    }
    SDL_Texture* getAparencia(){
        return apariencia->getApariencia();
    }

    SDL_Rect* getSrcRect(){
        return apariencia->getRect();
    }

    SDL_Rect* getDestRect(){
        return &destRect;
    }

    ~Personaje(){}
};

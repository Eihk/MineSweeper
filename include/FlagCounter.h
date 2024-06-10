#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include <iostream>


class FlagCounter{
public:
    FlagCounter(const int MaxBombs, SDL_Rect Rect);
    void IncrementCounter();
    void DecrementCounter();
    void Render(SDL_Renderer* Renderer) const;
    ~FlagCounter();

private:
    void Update();

    int _MaxCounter;
    int ValueDisplayed;

    SDL_Rect _SignRect;
    SDL_Rect _FirstNumberRect;
    SDL_Rect _SecondNumberRect;

    SDL_Rect _Rect;
    SDL_Color _Color = {255, 255, 255, 255};;
};
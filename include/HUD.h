#pragma once

#include <SDL.h>

#include "FlagCounter.h"
#include "Button.h"

#define yHud 80
#define DisplayWidth 86
#define DisplayHeight 50

class HUD{
public:
    HUD(const int BoardScreenWidth, const int MaxBombs);
    void Render(SDL_Renderer* Renderer);
    ~HUD();
private:
    Button _ResetButton;
    FlagCounter* _FlagCounter;

    const int Value = 0;

    friend class Board;
};
#pragma once

#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "Button.h"
#include "GameDifficulty.h"

class DifficultyButton : public Button {
public:
    DifficultyButton();
    DifficultyButton(SDL_Renderer* Renderer, SDL_Rect& rect, SDL_Color, GameDifficulty Difficulty, const char* Text);
    GameDifficulty GetDifficulty();

private:
    GameDifficulty _Difficulty;
};
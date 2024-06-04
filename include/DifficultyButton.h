#pragma once
#include "Button.h"
//#include <SDL_ttf.h>
#include <string>
#include "GameDifficulty.h"

class DifficultyButton : public Button {
public:
    DifficultyButton();
    DifficultyButton(SDL_Renderer* Renderer, SDL_Rect& rect, SDL_Color, GameDifficulty Difficulty, std::string Text);
    GameDifficulty GetDifficulty();

private:
    GameDifficulty _Difficulty;
};
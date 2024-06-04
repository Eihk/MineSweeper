#include "DifficultyButton.h"

DifficultyButton::DifficultyButton() : Button(){}

DifficultyButton::DifficultyButton(SDL_Renderer* Renderer, SDL_Rect& Rect, SDL_Color Color,
    GameDifficulty Difficulty, std::string Text) : Button(Rect, Color), _Difficulty(Difficulty){
    const int FontSize = 30;
    //TTF_Font* FontType = TTF_OpenFont("assets/Octin_Sports.ttf", 24);
    SDL_Color FontColor = {255, 255, 255, 255};

    //SDL_Surface* SurfaceMessage = TTF_RenderText_Solid(Sans, Text, FontColor);
}

GameDifficulty DifficultyButton::GetDifficulty(){
    return _Difficulty;
}
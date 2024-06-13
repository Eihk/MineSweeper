#include "DifficultyButton.h"

DifficultyButton::DifficultyButton() : Button(){}

DifficultyButton::DifficultyButton(SDL_Renderer* Renderer, SDL_Rect& Rect, SDL_Color Color,
    GameDifficulty Difficulty, const char* Text) : Button(Rect, Color), _Difficulty(Difficulty){
    const int FontSize = 30;
    TTF_Font* FontType = TTF_OpenFont("assets/Octin_Sports_Free.ttf", FontSize);
    SDL_Color FontColor = {255, 255, 255, 255};

    SDL_Surface* SurfaceMessage = TTF_RenderText_Solid(FontType, Text, FontColor);
    SDL_Texture* TextureMessage = SDL_CreateTextureFromSurface(Renderer, SurfaceMessage);

    SetTexture(TextureMessage);
    TTF_CloseFont(FontType);
}

GameDifficulty DifficultyButton::GetDifficulty(){
    return _Difficulty;
}


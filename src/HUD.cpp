#include "HUD.h"

HUD::HUD(const int BoardScreenWidth, const  int MaxBombs){
    SDL_Rect FlagRect = {10, (yHud - DisplayHeight)/2, DisplayWidth, DisplayHeight};
    _FlagCounter = new FlagCounter(MaxBombs, FlagRect);

    SDL_Rect ResetButtonRect = {BoardScreenWidth/2, (yHud - 32)/2, 32, 32};
    SDL_Color ButtonColor = {255, 255, 255, 255};
    _ResetButton = Button(ResetButtonRect, ButtonColor);

}

void HUD::Render(SDL_Renderer* Renderer){
    _ResetButton.Render(Renderer);
    _FlagCounter->Render(Renderer);
}

HUD::~HUD(){
    _FlagCounter = nullptr;
    delete _FlagCounter;
}
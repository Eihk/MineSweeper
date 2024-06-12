#include "HUD.h"

HUD::HUD(const int BoardScreenWidth, const  int MaxBombs){
    /* Flag Counter */
    SDL_Rect FlagRect = {10, (yHud - DisplayHeight)/2, DisplayWidth, DisplayHeight};
    _FlagCounter = new FlagCounter(MaxBombs, FlagRect);

    /* Timer Counter */
    SDL_Rect TimerRect = {BoardScreenWidth - DisplayWidth - 10, (yHud - DisplayHeight)/2, DisplayWidth, DisplayHeight};
    _TimerCounter = new TimerCounter(TimerRect);

    /* Reset Button*/
    SDL_Rect ResetButtonRect = {BoardScreenWidth/2 - 16, (yHud - 32)/2, 32, 32};
    SDL_Color ButtonColor = {255, 255, 255, 255};
    _ResetButton = Button(ResetButtonRect, ButtonColor);
}

void HUD::Render(SDL_Renderer* Renderer){
    _ResetButton.Render(Renderer);
    _FlagCounter->Render(Renderer);
    _TimerCounter->Render(Renderer);
}

void HUD::SetButtonLostTexture(SDL_Renderer* Renderer){
    SDL_Surface* SurfaceImage = SDL_LoadBMP(LostEmojiPath);
    SDL_SetColorKey(SurfaceImage, SDL_TRUE, SDL_MapRGB(SurfaceImage->format, 255, 255, 255));
    if(SurfaceImage != nullptr){
        SDL_Texture* LostTexture = SDL_CreateTextureFromSurface(Renderer, SurfaceImage);
        SDL_FreeSurface(SurfaceImage);
        _ResetButton.SetTexture(LostTexture);
    }
}

void HUD::SetButtonWinTexture(SDL_Renderer* Renderer){
    SDL_Surface* SurfaceImage = SDL_LoadBMP(WinEmojiPath);
    SDL_SetColorKey(SurfaceImage, SDL_TRUE, SDL_MapRGB(SurfaceImage->format, 255, 255, 255));
    if(SurfaceImage != nullptr){
        SDL_Texture* WinTexture = SDL_CreateTextureFromSurface(Renderer, SurfaceImage);
        SDL_FreeSurface(SurfaceImage);
        _ResetButton.SetTexture(WinTexture);
    }
}

void HUD::SetButtonPlayingTexture(SDL_Renderer* Renderer){
    SDL_Surface* SurfaceImage = SDL_LoadBMP(PlayingEmojiPath);
    SDL_SetColorKey(SurfaceImage, SDL_TRUE, SDL_MapRGB(SurfaceImage->format, 255, 255, 255));
    if(SurfaceImage != nullptr){
        SDL_Texture* PlayingTexture = SDL_CreateTextureFromSurface(Renderer, SurfaceImage);
        SDL_FreeSurface(SurfaceImage);
        _ResetButton.SetTexture(PlayingTexture);
    }
}

void HUD::HandleMouseClick(const SDL_Event& event, const std::function<void()>& HandleReset){
    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse, &yMouse);

    if (event.button.button == SDL_BUTTON_LEFT){
        if(_ResetButton.IsMouseInside(xMouse, yMouse)){
            HandleReset();
        }
    }
}

HUD::~HUD(){
    _FlagCounter->~FlagCounter();
    _TimerCounter->~TimerCounter();
    _FlagCounter = nullptr;
    _TimerCounter = nullptr;
}
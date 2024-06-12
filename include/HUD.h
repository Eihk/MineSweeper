#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "FlagCounter.h"
#include "TimerCount.h"
#include "Button.h"
#include <iostream>
#include <functional>

#define yHud 80
#define DisplayWidth 86
#define DisplayHeight 50

#define LostEmojiPath "assets/LostEmoji.bmp"
#define PlayingEmojiPath "assets/StartingEmoji.bmp"
#define WinEmojiPath "assets/AlmostEmoji.bmp"

class HUD{
public:
    HUD(const int BoardScreenWidth, const int MaxBombs);
    void Render(SDL_Renderer* Renderer);

    void SetButtonLostTexture(SDL_Renderer* Renderer);
    void SetButtonWinTexture(SDL_Renderer* Renderer);
    void SetButtonPlayingTexture(SDL_Renderer* Renderer);
    void SetReturnButtonTexture(SDL_Renderer* Renderer);

    void HandleMouseClick(const SDL_Event &event, const std::function<void()>& HandleReset, const std::function<void()>& HandleReturnMenu);

    ~HUD();
private:
    Button _ResetButton;
    Button _ReturnToMenuButton;
    FlagCounter* _FlagCounter;
    TimerCounter* _TimerCounter;


    friend class Board;
};
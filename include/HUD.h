#pragma once

#include <SDL.h>

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
#define WinEmojiPath "assets/AmostEmoji.bmp"

class HUD{
public:
    HUD(const int BoardScreenWidth, const int MaxBombs);
    void Render(SDL_Renderer* Renderer);

    void SetButtonLostTexture(SDL_Renderer* Renderer);
    void SetButtonWinTexture(SDL_Renderer* Renderer);
    void SetButtonPlayingTexture(SDL_Renderer* Renderer);
    void HandleMouseClick(const SDL_Event &event, const std::function<void()>& HandleReset);


    ~HUD();
private:
    Button _ResetButton;
    FlagCounter* _FlagCounter;
    TimerCounter* _TimerCounter;

    const int Value = 0;

    friend class Board;
};
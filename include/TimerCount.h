#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <chrono>
#include <ctime>
#include <cmath>
#include <string>

#include <iostream>

class TimerCounter{
public:
    TimerCounter(SDL_Rect Rect);
    void StartTimer();
    void StopTimer();
    void Update();
    void Render(SDL_Renderer* Renderer);
    ~TimerCounter();

private:
    int StartTime;
    int ElapsedTime;
    bool IsRunningTimer = false;

    SDL_Rect _FirstNumberRect;
    SDL_Rect _SecondNumberRect;
    SDL_Rect _ThirdNumberRect;
    
    std::string _FirstNumber;
    std::string _SecondNumber;
    std::string _ThirdNumber;

    SDL_Rect _Rect;
    SDL_Color _Color = {255, 255, 255, 255};;
};
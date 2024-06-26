#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Menu.h"
#include "Board.h"
#include "GameDifficulty.h"
#include "HUD.h"


enum class EGameState {
    EGS_Menu,
    EGS_Board,
    EGS_Reset,
    EGS_Exit
};

class MineSweeper{
private:
    SDL_Window* _Window;
    SDL_Renderer* _Renderer;
    EGameState GameState;
    GameDifficulty _GameDifficulty;

    const int MenuScreenWidth = 204;
    const int MenuScreenHeight = 190;

    void MenuScreen();
    void BoardScreen();

public:
    MineSweeper();
    void Play();
    ~MineSweeper();
};
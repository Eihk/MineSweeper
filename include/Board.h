#pragma once

#include <SDL.h>
#include <Cell.h>
#include "GameDifficulty.h"

enum class EBoardState{
    EBS_Initializing,
    EBS_Playing,
    EBS_Lose,
    EBS_Win,
};

class Board{

public:
    Board(SDL_Renderer* renderer, const GameDifficulty& GameDifficulty);
    int GetIndex(const int row, const int col);
    void RenderBoard(SDL_Renderer* renderer);
    ~Board();

private:
    int _Rows;
    int _Cols;
    int _Bombs;

    EBoardState BoardState = EBoardState::EBS_Initializing;
    Cell* _Map;
};


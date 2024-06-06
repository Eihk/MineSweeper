#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>
#include <random>
#include <functional>

#include "Cell.h"
#include "GameDifficulty.h"
#include "Interface.h"


enum class EBoardState{
    EBS_Initializing,
    EBS_FirstMove,
    EBS_Playing,
    EBS_Lose,
    EBS_Win,
};

class Board{

public:
    Board(SDL_Renderer *renderer, const GameDifficulty &GameDifficulty);
    void GenerateCells(int yHud);
    int GetIndex(const int row, const int col);
    void RenderBoard(SDL_Renderer *renderer);
    void HandleMouseClick(const SDL_Event &event, const std::function<void(Cell &)> &HandleDifficulty);
    ~Board();

private:
    int _Rows;
    int _Cols;
    int _Bombs;

    std::vector<int> BombsIndexList;

    EBoardState BoardState = EBoardState::EBS_Initializing;
    Cell* _Map;

    void GenerateBombs(const int FirstClickedRow, const int FirstClickedCol);
    void GenerateNumbers();
    void GenerateCells();
    void AddBomb(const int FirstClickedRow, const int FirstClickedCol);
    bool IsCellAvailable(const int xFutureBombPos, const int yFutureBombPos, const int FirstClickedRow, const int FirstClickedCol);
};


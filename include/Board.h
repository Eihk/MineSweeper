#pragma once

#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include <random>

#include "Cell.h"
#include "GameDifficulty.h"
#include "Interface.h"
#include "HUD.h"


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
    int GetIndex(const int row, const int col);
    void RenderBoard(SDL_Renderer *renderer, HUD& HUD);
    void HandleMouseClick(const SDL_Event &event, HUD& HUD);
    void HandleCellClick(Cell &CurrentCell, const SDL_Event &event, const int xMouse, const int yMouse, HUD& Hud);
    ~Board();

private:
    int _Rows;
    int _Cols;
    int _Bombs;
    int _MaxCellsIndex;
    int _CellsToOpen;
    SDL_Renderer *_Renderer;

    std::vector<int> BombsIndexList;

    EBoardState BoardState = EBoardState::EBS_Initializing;
    Cell* _Map;

    void GenerateBombs(const int FirstClickedRow, const int FirstClickedCol);
    void GenerateNumbers();
    void GenerateCells();
    void AddBomb(const int FirstClickedRow, const int FirstClickedCol);
    bool IsCellAvailable(const int xFutureBombPos, const int yFutureBombPos, const int FirstClickedRow, const int FirstClickedCol);
    int GetNeighborBombs(const int Row, const int Col);
    std::vector<int> GetNeighborCell(Cell& ThisCell);
    bool IsBombPlantedAt(const int Row, const int Col);
    void ExpandFrom(Cell& FromThisCell, HUD& Hud);
    bool InsideIndexRange(const int Row, const int Col);
    void ShowAllBombs();

public:
    inline int GetRemainingCellsToOpen() const {return _CellsToOpen;}
};


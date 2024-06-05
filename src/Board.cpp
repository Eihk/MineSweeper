#include "Board.h"
#include <iostream>

Board::Board(SDL_Renderer* renderer, const GameDifficulty& GameDifficulty){
    _Rows = GameDifficulty.Rows;
    _Cols = GameDifficulty.Cols;
    _Bombs = GameDifficulty.Bombs;

    const int MaxNumber = 9;
    const SDL_Color NumbersColor[MaxNumber] =
    {{  0,   0,   0,  0},  //0 = Nothing (wont be used but kept to make index make more sense)
    { 20,  57, 168, 255},  //1 = BLUE
    { 20, 148,  18, 255},  //2 = GREEN
    {179,  30,  30, 255},  //3 = RED
    {103,  28, 173, 255},  //4 = PURPLE
    {133,  20,  20, 255},  //5 = MAROON
    {  9, 179, 164, 255},  //6 = TURQUOISE
    {  0,   0,   0, 255},  //7 = BLACK
    {255, 255, 255, 255}}; //8 = WHITE

    int yHud = 120;

    _Map = new Cell[_Rows * _Cols]; 
    int xCell = CellGap;
    int yCell = yHud + CellGap;

    for (int row = 0; row < _Rows; row++){
        for (int col = 0; col < _Cols; col++){
            SDL_Rect rect = {xCell, yCell, CellSize, CellSize};
            _Map[GetIndex(row, col)] = Cell(rect);
            xCell += CellSize + CellGap;
        }
        xCell = CellGap;
        yCell += CellSize + CellGap; 
    }
}

int Board::GetIndex(const int row, const int col){
    return row * _Cols + col;
}

void Board::RenderBoard(SDL_Renderer* renderer){
    int yHud = 120;
    int xCell = CellGap;
    int yCell = yHud + CellGap;
    for (int row = 0; row < _Rows; row++){
        for (int col = 0; col < _Cols; col++){
            _Map[GetIndex(row, col)].Render(renderer);
            
            xCell += CellSize + CellGap;
        }
        xCell = CellGap;
        yCell += CellSize + CellGap; 
    }
}

void Board::HandleMouseClick(const SDL_Event& event, const std::function<void(Cell&)>& HandleCell){
    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse, &yMouse);

    int yHud = 120;
    int xCell = CellGap;
    int yCell = yHud + CellGap;
    for (int row = 0; row < _Rows; row++){
        for (int col = 0; col < _Cols; col++){
            if(_Map[GetIndex(row, col)].IsMouseInside(xMouse, yMouse)){
                HandleCell(_Map[GetIndex(row, col)]);
            }
            xCell += CellSize + CellGap;
        }
        xCell = CellGap;
        yCell += CellSize + CellGap; 
    }
}

void Board::GenerateBomb(){
    //_Bombs // Number of bomb
    const int NumberOfCells = _Rows * _Cols;
    

}

Board::~Board(){
    delete[] _Map;
}
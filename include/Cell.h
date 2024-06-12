#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Button.h"

#define NUMBER_COUNT 9
#define CellGap 2
#define CellSize 32

#define BombFilePath "assets/Bomb.bmp"
#define FlagFilePath "assets/Flag.bmp"

enum class ECellType{
    ECT_Nothing,
    ECT_Number,
    ECT_Bomb,
};

enum class ECellState{
    ECS_Closed,
    ECS_Opened,
};

class Cell: public Button{

public:
    Cell();
    Cell(const SDL_Rect& rect, const int row, const int col);
    ~Cell();

    void ChangeCellType(ECellType NewType);
    void OpenCell(SDL_Renderer* _Renderer);
    void UpdateCellType();
    void AddNumber(SDL_Renderer* _Renderer, const char* Text, SDL_Color Color);

    bool IsCellOpen();
    bool IsCellBomb();
    bool IsCellNothing();
    bool IsCellNumber();

    void RemoveFlag();
    void GetFlag(SDL_Renderer* _Renderer);

    int _Row;
    int _Col;

    static SDL_Color BaseColor;
    static SDL_Color PressedColor;
    static SDL_Color MarkColor;

    static SDL_Texture* TextureOfNumbers[NUMBER_COUNT];
    static SDL_Texture* FlagTexture;
    static SDL_Texture* BombTexture;

private:

    bool _IsFlagged = false;
    const char* NumberText;
    SDL_Color TextColor;

    ECellType _CellType = ECellType::ECT_Nothing;
    ECellState _CellState = ECellState::ECS_Closed;

    SDL_Texture* TextureMessage = nullptr;
    
public:
    inline ECellState GetCellState() const {return _CellState;}
    inline ECellType GetCellType() const {return _CellType;}
    inline bool IsFlagged() const {return _IsFlagged;}
};
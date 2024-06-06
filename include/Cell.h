#pragma once
#include <SDL.h>
#include "Button.h"

#define NUMBER_COUNT 9
#define CellGap 2
#define CellSize 32

enum class ECellType{
    ECT_Nothing,
    ECT_Number,
    ECT_Bomb,
};

enum class ECellState{
    ECS_Unflipped,
    ECS_Flipped,
};

class Cell: public Button{

public:
    Cell();
    Cell(const SDL_Rect& rect);

    void FlipCell();
    void ChangeCellType(ECellType NewType);
    void UpdateCellType();

    static SDL_Color BaseColor;
    static SDL_Color PressedColor;
    static SDL_Color MarkColor;

    static SDL_Texture* TextureOfNumbers[NUMBER_COUNT];
    static SDL_Texture* FlagTexture;
    static SDL_Texture* BombTexture;

private:
    ECellType CellType = ECellType::ECT_Nothing;
    ECellState CellState = ECellState::ECS_Unflipped;
    
public:
    inline ECellState GetCellState() const {return CellState;}
};
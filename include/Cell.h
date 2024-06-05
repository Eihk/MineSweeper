#pragma once
#include <SDL.h>
#include "Button.h"

#define NUMBER_COUNT 9
#define CellGap 4
#define CellSize 32

enum class ECellType{
    ECT_Nothing,
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

    static SDL_Color BaseColor;
    static SDL_Color PressedColor;
    static SDL_Color MarkColor;

    static SDL_Texture* TextureOfNumbers[NUMBER_COUNT];
    static SDL_Texture* FlagTexture;
    static SDL_Texture* BombTexture;

private:
    ECellType CellType;
    ECellState CellState = ECellState::ECS_Unflipped;
    
public:
    inline ECellState GetCellState() const {return CellState;}
};
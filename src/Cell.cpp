#include <Cell.h>

#include <iostream>

SDL_Color Cell::BaseColor = {114, 166, 176, 255};
SDL_Color Cell::PressedColor = {200, 200, 200, 255};
SDL_Color Cell::MarkColor = {0, 0, 0 , 0};

SDL_Texture* Cell::TextureOfNumbers[NUMBER_COUNT] = {};
SDL_Texture* Cell::FlagTexture = nullptr;
SDL_Texture* Cell::BombTexture = nullptr;



Cell::Cell() : Button(){}
Cell::Cell(const SDL_Rect& rect, const int row, const int col) : Button(rect, BaseColor){
    _Row = row;
    _Col = col;
}

void Cell::ChangeCellType(ECellType NewType){
    CellType = NewType;
}

void Cell::OpenCell(){
    if(TextureMessage != nullptr){
        SetTexture(TextureMessage);
    }
    if(IsCellBomb()){
        ChangeColorTo({255, 0, 0, 255});
    } else{
        ChangeColorTo(PressedColor);
    }
    CellState = ECellState::ECS_Opened;
}

void Cell::AddNumber(SDL_Renderer* _Renderer, const char* Text, SDL_Color Color){
    const int FontSize = 30;
    TTF_Font* FontType = TTF_OpenFont("assets/Octin_Sports_Free.ttf", FontSize);

    SDL_Surface* SurfaceMessage = TTF_RenderText_Solid(FontType, Text, Color);
    TextureMessage = SDL_CreateTextureFromSurface(_Renderer, SurfaceMessage);

    SDL_RenderCopy(_Renderer, TextureMessage, NULL, &GetRect());
    TTF_CloseFont(FontType);
}

bool Cell::IsCellOpen(){
    return CellState == ECellState::ECS_Opened;
}

bool Cell::IsCellBomb(){
    return CellType == ECellType::ECT_Bomb;
}

bool Cell::IsCellNothing(){
    return CellType == ECellType::ECT_Nothing;
}

bool Cell::IsCellNumber(){
    return CellType == ECellType::ECT_Number;
}
#include <Cell.h>

#include <iostream>

SDL_Color Cell::BaseColor = {255, 255, 255, 255};
SDL_Color Cell::PressedColor = {0, 0, 0, 0};
SDL_Color Cell::MarkColor = {0, 0, 0 , 0};

SDL_Texture* Cell::TextureOfNumbers[NUMBER_COUNT] = {};
SDL_Texture* Cell::FlagTexture = nullptr;
SDL_Texture* Cell::BombTexture = nullptr;



Cell::Cell() : Button(){}
Cell::Cell(const SDL_Rect& rect) : Button(rect, BaseColor){}

void Cell::FlipCell(){
    CellState = ECellState::ECS_Flipped;
    ChangeColorTo(PressedColor);
}

void Cell::ChangeCellType(ECellType NewType){
    CellType = NewType;
    UpdateCellType();
}

void Cell::UpdateCellType(){
    switch (CellType)
    {
    case ECellType::ECT_Bomb:
        ChangeColorTo({255, 0, 0, 255});
        break;
    case ECellType::ECT_Number:
        //ChangeColorTo({0, 0, 255, 255});
        break;
    default:
        break;
    }
}

void Cell::AddNumber(SDL_Renderer* _Renderer, const char* Text, SDL_Color Color){
    const int FontSize = 30;
    TTF_Font* FontType = TTF_OpenFont("assets/Octin_Sports_Free.ttf", FontSize);

    SDL_Surface* SurfaceMessage = TTF_RenderText_Solid(FontType, Text, Color);
    SDL_Texture* TextureMessage = SDL_CreateTextureFromSurface(_Renderer, SurfaceMessage);

    //SDL_RenderCopy(Renderer, TextureMessage, NULL, &GetRect());
    SetTexture(TextureMessage);
    TTF_CloseFont(FontType);
}
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
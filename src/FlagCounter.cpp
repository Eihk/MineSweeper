#include "FlagCounter.h"

FlagCounter::FlagCounter(const int MaxBombs, SDL_Rect Rect){
    _MaxCounter = MaxBombs;
    ValueDisplayed = MaxBombs;
    _Rect = Rect;

    const int HeightPos = _Rect.y + _Rect.h*1/8;
    const int Gap = 2;
    const int WidthSize = Rect.w/3 - 5*Gap/3;
    const int HeightSize = _Rect.h*3/4;
    _SignRect = {_Rect.x + 2*Gap + 5, HeightPos, WidthSize - 10, HeightSize};
    _FirstNumberRect = {_Rect.x + WidthSize + 3*Gap -5, HeightPos, WidthSize, HeightSize};
    _SecondNumberRect = {_Rect.x + 2*WidthSize + 4*Gap -5, HeightPos, WidthSize, HeightSize};
}

void FlagCounter::IncrementCounter(){
    ValueDisplayed++;
}

void FlagCounter::DecrementCounter(){
    ValueDisplayed--;
}

void FlagCounter::Render(SDL_Renderer* Renderer) const{
    SDL_SetRenderDrawColor(Renderer, _Color.r, _Color.g, _Color.b, _Color.a);
    SDL_RenderDrawRect(Renderer, &_Rect);

    /* Draw Numbers */
    const int FontSize = 30;
    TTF_Font* FontType = TTF_OpenFont("assets/Octin_Sports_Free.ttf", FontSize);

    const int FirstDisplay = std::abs(ValueDisplayed / 10);
    const int SecondDisplay = std::abs(ValueDisplayed % 10);

    if(ValueDisplayed < 0){
        std::string Str0 = "-";
        const char* SignChar = Str0.c_str();
        SDL_Surface* SignSurfaceMessage = TTF_RenderText_Solid(FontType, SignChar, {255, 150, 0, 255});
        SDL_Texture* SignTextureMessage = SDL_CreateTextureFromSurface(Renderer, SignSurfaceMessage);
        SDL_RenderCopy(Renderer, SignTextureMessage, NULL, &_SignRect);
    }
    std::string Str1 = std::to_string(FirstDisplay);
    const char* FirstNumber = Str1.c_str();
    std::string Str2 =  std::to_string(SecondDisplay);
    const char* SecondNumber = Str2.c_str();


    SDL_Surface* FirstSurfaceMessage = TTF_RenderText_Solid(FontType, FirstNumber, {255, 150, 0, 255});
    SDL_Texture* FirstTextureMessage = SDL_CreateTextureFromSurface(Renderer, FirstSurfaceMessage);
    
    SDL_Surface* SecondSurfaceMessage = TTF_RenderText_Solid(FontType, SecondNumber, {255, 150, 0, 255});
    SDL_Texture* SecondTextureMessage = SDL_CreateTextureFromSurface(Renderer, SecondSurfaceMessage);

    SDL_RenderCopy(Renderer, FirstTextureMessage, NULL, &_FirstNumberRect);
    SDL_RenderCopy(Renderer, SecondTextureMessage, NULL, &_SecondNumberRect);

    TTF_CloseFont(FontType);
}

FlagCounter::~FlagCounter(){

}
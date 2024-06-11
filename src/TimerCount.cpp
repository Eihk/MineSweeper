#include "TimerCount.h"

TimerCounter::TimerCounter(SDL_Rect Rect){
    _Rect = Rect;

    const int FontSize = 30;
    TTF_Font* FontType = TTF_OpenFont("assets/Octin_Sports_Free.ttf", FontSize);

    const int HeightPos = _Rect.y + _Rect.h*1/8;
    const int Gap = 2;
    const int WidthSize = Rect.w/3 - 5*Gap/3;
    const int HeightSize = _Rect.h*3/4;
    _FirstNumberRect = {_Rect.x + 2*Gap, HeightPos, WidthSize, HeightSize};
    _SecondNumberRect = {_Rect.x + WidthSize + 3*Gap, HeightPos, WidthSize, HeightSize};
    _ThirdNumberRect = {_Rect.x + 2*WidthSize + 4*Gap, HeightPos, WidthSize, HeightSize};

    const int FirstValue = std::abs(0);
    const int SecondValue = std::abs(0);
    const int ThirdValue = std::abs(0);

    _FirstNumber = std::to_string(FirstValue);
    _SecondNumber = std::to_string(SecondValue);
    _ThirdNumber = std::to_string(ThirdValue);
}

void TimerCounter::StartTimer(){
    StartTime = (int)time(NULL);
    IsRunningTimer = true;
}

void TimerCounter::StopTimer(){
    IsRunningTimer = false;
}

void TimerCounter::Update(){
    /* Update Timer */
    ElapsedTime = (int)time(NULL) - StartTime;
    if(IsRunningTimer){
        if(ElapsedTime > 0){
            const int FirstValue = std::abs(ElapsedTime / 100);
            const int SecondValue = std::abs((ElapsedTime / 10) % 10);
            const int ThirdValue = std::abs(ElapsedTime % 10);

            _FirstNumber = std::to_string(FirstValue);
            _SecondNumber = std::to_string(SecondValue);
            _ThirdNumber = std::to_string(ThirdValue);
        }
    }
}

void TimerCounter::Render(SDL_Renderer* Renderer){

    Update();

    SDL_SetRenderDrawColor(Renderer, _Color.r, _Color.g, _Color.b, _Color.a);
    SDL_RenderDrawRect(Renderer, &_Rect);

    /* Draw Numbers */
    const int FontSize = 30;
    TTF_Font* FontType = TTF_OpenFont("assets/Octin_Sports_Free.ttf", FontSize);

    const char* FirstDiplay = _FirstNumber.c_str();
    const char* SecondDisplay = _SecondNumber.c_str();
    const char* ThirdDisplay = _ThirdNumber.c_str();

    SDL_Surface* FirstSurfaceMessage = TTF_RenderText_Solid(FontType, FirstDiplay, {255, 150, 0, 255});
    SDL_Texture* FirstTextureMessage = SDL_CreateTextureFromSurface(Renderer, FirstSurfaceMessage);
    
    SDL_Surface* SecondSurfaceMessage = TTF_RenderText_Solid(FontType, SecondDisplay, {255, 150, 0, 255});
    SDL_Texture* SecondTextureMessage = SDL_CreateTextureFromSurface(Renderer, SecondSurfaceMessage);

    SDL_Surface* ThirdSurfaceMessage = TTF_RenderText_Solid(FontType, ThirdDisplay, {255, 150, 0, 255});
    SDL_Texture* ThirdTextureMessage = SDL_CreateTextureFromSurface(Renderer, ThirdSurfaceMessage);

    SDL_RenderCopy(Renderer, FirstTextureMessage, NULL, &_FirstNumberRect);
    SDL_RenderCopy(Renderer, SecondTextureMessage, NULL, &_SecondNumberRect);
    SDL_RenderCopy(Renderer, ThirdTextureMessage, NULL, &_ThirdNumberRect);

    TTF_CloseFont(FontType);


}

TimerCounter::~TimerCounter(){

}
#include "Menu.h"

Menu::Menu(SDL_Renderer* Renderer, const int ScreenWidth, const int ScreeHeight){
    InitButton(Renderer);
}

void Menu::InitButton(SDL_Renderer* Renderer){
    GameDifficulty EasyMode = {9, 9, 10};
    GameDifficulty MediumMode = {16, 16, 40};
    GameDifficulty ExpertMode = {16, 30, 99};
    GameDifficulty DifficultyList[3] = {EasyMode, MediumMode, ExpertMode};

    const char* DifficultyName[3] = {"Easy", "Medium", "Expert"};

    const int VerticalGap = 10;
    const int HorizontalGap = 2;
    const int ButtonWidth = 200;
    const int ButtonHeight = 50;
    const SDL_Color EasyButtonColor = {114, 200, 110, 255};
    const SDL_Color MediumButtonColor = {255, 166, 100, 255};
    const SDL_Color ExpertButtonColor = {255, 50, 50};
    const SDL_Color ColorList[3] = {EasyButtonColor, MediumButtonColor, ExpertButtonColor};
    const SDL_Color ButtonColor = {114, 166, 176, 255};

    int xButton = HorizontalGap;
    int yButton = VerticalGap;
    for(int idx = 0; idx < 3; idx ++){
        SDL_Rect Button = {xButton, yButton, ButtonWidth, ButtonHeight}; //SDL_Renderer* Renderer, SDL_Rect& rect, SDL_Color, String Text
        DifficultyButtons[idx] = DifficultyButton(Renderer, Button, ColorList[idx], DifficultyList[idx], DifficultyName[idx]);
        yButton += ButtonHeight + VerticalGap;
    }
}

void Menu::Render(SDL_Renderer* Renderer){
    for (auto& Button: DifficultyButtons){
        Button.Render(Renderer);
    }
}

void Menu::HandleMouseClick(const SDL_Event& event, const std::function<void(const GameDifficulty&)>& HandleDifficulty){
    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse, &yMouse);

    for(auto& Button : DifficultyButtons){
        if(Button.IsMouseInside(xMouse, yMouse)){
            if(event.button.button == SDL_BUTTON_LEFT){
                HandleDifficulty(Button.GetDifficulty());
            }
        }
    }
}

Menu::~Menu(){

}
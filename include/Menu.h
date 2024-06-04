#pragma once

#include <SDL.h>
#include "DifficultyButton.h"
#include "GameDifficulty.h"
#include "Interface.h"


class Menu : public ClickInterface{

public:
    Menu(SDL_Renderer* Renderer, const int ScreenWidth, const int ScreeHeight);
    void HandleMouseClick(const SDL_Event& event, const std::function<void(const GameDifficulty&)>& HandleDifficulty) override;
    void Render(SDL_Renderer* Renderer);
    ~Menu();

private:
    DifficultyButton DifficultyButtons[3];
    void InitButton(SDL_Renderer* Renderer);

};
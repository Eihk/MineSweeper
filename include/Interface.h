#pragma once
#include <SDL.h>
#include <iostream>
#include <functional>
#include "GameDifficulty.h"

class ClickInterface {
public:
    virtual void HandleMouseClick(const SDL_Event& event, const std::function<void(const GameDifficulty&)>& HandleDifficulty) = 0;
};
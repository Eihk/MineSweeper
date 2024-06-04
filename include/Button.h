#pragma once
#include <SDL.h>
#include "UI_Element.h"

class Button : public UI_Element {
    public:
        Button();
        Button(const SDL_Rect& rect, const SDL_Color& color);
        bool IsMouseInside(const int xMouse, const int yMouse) const;
};
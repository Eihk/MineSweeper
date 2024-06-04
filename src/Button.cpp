#include "Button.h"

Button::Button() : UI_Element(){}

Button::Button(const SDL_Rect& rect, const SDL_Color& color) : UI_Element(rect, color){
}

bool Button::IsMouseInside(const int xMouse, const int yMouse) const {

    bool Inside = true;
    const SDL_Rect rect = GetRect();
    if(xMouse < rect.x){ //Left of the Button
        Inside = false;
    }
    else if(xMouse > rect.x + rect.w){ //Right of the Button
        Inside = false;
    }
    else if(yMouse < rect.y){ //Above the Button
        Inside = false;
    }
    else if(yMouse > rect.y + rect.h){ //Below the Button
        Inside = false;
    }
    return Inside;
}
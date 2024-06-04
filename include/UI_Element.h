#pragma once
#include <SDL.h>

class UI_Element {

private:
    SDL_Rect _Rect;
    SDL_Color _Color;

    SDL_Texture* _Texture;
    SDL_Rect _TextureRect;

    void CenterTexture();

public:    
    UI_Element();
    UI_Element(const SDL_Rect& rect, const SDL_Color color);
    void SetTexture(SDL_Texture* texture);
    void ChangeColorTo(const SDL_Color& color);
    SDL_Rect GetRect() const;
    void Render(SDL_Renderer* render) const;
    void Free();
};
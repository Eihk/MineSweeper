#include "UI_Element.h"

#include <iostream>

UI_Element::UI_Element(){
    _Rect.x = 0;
    _Rect.y = 0;
    _Rect.w = 32;
    _Rect.h = 32;

    _Color.r = 255;
    _Color.g = 255;
    _Color.b = 255;
    _Color.a = 255;

    _Texture = nullptr;
    _TextureRect.x = 0;
    _TextureRect.y = 0;
    _TextureRect.w = 0;
    _TextureRect.y = 0;
}

UI_Element::UI_Element(const SDL_Rect& rect, const SDL_Color color) {
    _Rect = rect;
    _Color = color;
    _Texture = nullptr;
    _TextureRect.x = 0;
    _TextureRect.y = 0;
    _TextureRect.w = 0;
    _TextureRect.y = 0;
}

void UI_Element::CenterTexture() {
    _TextureRect.y = _Rect.y + 0.5 * (_Rect.h - _TextureRect.h);
	_TextureRect.x = _Rect.x + 0.5 * (_Rect.w - _TextureRect.w);
}        

void UI_Element::SetTexture(SDL_Texture* texture) {
    _Texture = texture;
    SDL_QueryTexture(texture, NULL, NULL, &_TextureRect.w, &_TextureRect.h);
    CenterTexture();
}

void UI_Element::ChangeColorTo(const SDL_Color& color) {
    _Color = color;
}

SDL_Rect UI_Element::GetRect() const {
    return _Rect;
}

void UI_Element::Render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, _Color.r, _Color.g, _Color.b, _Color.a);
    SDL_RenderFillRect(renderer, &_Rect);

    if (_Texture != nullptr) {
        SDL_RenderCopy(renderer, _Texture, NULL, &_TextureRect);
    }
}

void UI_Element::Free() {
    SDL_DestroyTexture(_Texture);
    _Texture = nullptr;
}
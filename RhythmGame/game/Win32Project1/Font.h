#pragma once

#include "Texture.h"
#include "SDL_ttf.h"



class Font : public Texture
{
private:
	TTF_Font* _font;
	SDL_Color _fontColor;

public:
	Font(const char* fontName, int fontSize);
	~Font();

	void SetText(const char* text, int x, int y);
};
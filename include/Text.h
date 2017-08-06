#ifndef TEXT_H_
#define TEXT_H_

#include <iostream>
#include <string>

#include <SDL_ttf.h>
#include <SDL.h>

#include "Window.h"
#include "InputHandler.h"
#include "Resources.h"


#define TEXT_BLACK SDL_Color{0,0,0}
#define TEXT_WHITE SDL_Color{255,255,255}

#define TEXT_RED SDL_Color{255,0,0}
#define TEXT_GREEN SDL_Color{0,255,0}
#define TEXT_BLUE SDL_Color{0,0,255}

#define TEXT_MAGENTA SDL_Color{149,57,85}

enum TextStyle{
    SOLID,
    SHADED,
    BLENDED
};

class Text {
public:
	Text(std::string fontFile, int fontSize, TextStyle style, std::string text, int x, int y, SDL_Color color);
	Text(std::string fontFile, int fontSize, TextStyle style, std::string text, int x= 0, int y=0, int r = 0, int g = 0, int b = 0, int a = 0);
	~Text();

	void Initialize();

	void Render();
	void SetPos(int x, int y, bool centerX = false, bool centerY = false);
	void SetX(int x, bool centered = false);
	void SetY(int y, bool centered = false);
	void SetColor(SDL_Color color);
	void SetColor(int r, int g, int b, int a);
	void SetStyle(TextStyle style);
	void SetFontSize(int fontSize);
	void SetText(std::string text);
    int GetWidth();
    int GetX();
    int GetY();
    bool IsMouseInside();

private:
	void RemakeTexture();

	std::string fontFile;
	std::string text;

	TTF_Font* font;
	SDL_Texture* texture;
	TextStyle style;
	SDL_Color color;

	int fontSize;
	SDL_Rect box;
	static bool Initialized;
};

#endif

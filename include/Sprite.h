#ifndef SPRITE_H
#define SPRITE_H

#include <SDL_image.h>
#include <string>
#include <iostream>

#include "Window.h"
#include "Resources.h"

using std::string;
using std::cout;
using std::endl;
class Sprite
{
    public:
        Sprite(string path, int x = 0, int y = 0);
        Sprite();
        virtual ~Sprite();
        int GetWidth();
        int GetHeight();
        void Render(int x = 0, int y = 0);
        int GetX();
        int GetY();
        void SetX(int x);
        void SetY(int y);
        void Resize(int w, int h);
        void Clip(int w, int h, int x = 0, int y = 0);

    protected:

    private:
        SDL_Texture* img;
        SDL_Surface* aux;
        void Open(string path);
        SDL_Rect imgRect;
        SDL_Rect srcRect;
        string path;
};

#endif // SPRITE_H

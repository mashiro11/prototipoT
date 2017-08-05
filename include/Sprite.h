#ifndef SPRITE_H
#define SPRITE_H

#include <SDL_image.h>
#include <string>
#include <iostream>

#include "Window.h"
#include "Resources.h"
#include "InputHandler.h"

using std::string;
using std::cout;
using std::endl;
class Sprite
{
    public:
        Sprite(string path, int x = 0, int y = 0);
        virtual ~Sprite();
        int GetWidth();
        int GetHeight();
        void Render();
        int GetX();
        int GetY();
        void SetX(int x);
        void SetY(int y);
        void SetHeight(int h);
        void SetPosition(int x, int y);
        void Resize(int w, int h);
        void Clip(int w, int h, int x = 0, int y = 0);
        void SetRotationAngle(double angle);
        void SetRotationPoint(SDL_Point pt);
        void Transform(int w, int h);
        bool IsMouseInside();
        void SlideClip(int amountX, int amountY);
        string GetPath();
        void SetAlpha(int alpha);

    protected:

    private:
        SDL_Texture* img;
        SDL_Surface* aux;
        void Open(string path);
        SDL_Rect imgRect;
        SDL_Rect srcRect;
        string path;
        SDL_Point pt;
        double angle;
        Uint32 alpha;
};

#endif // SPRITE_H

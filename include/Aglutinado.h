#ifndef AGLUTINADO_H
#define AGLUTINADO_H

#include <SDL.h>
#include <unordered_map>
#include <string>
#include <iostream>

#include "ScreenObject.h"
#include "InputHandler.h"
#include "Setor.h"
#include "Point.h"
#include "Sprite.h"

#define PI 3.1415
#define STOP_ANGLE 315

using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::pair;

class Aglutinado : public ScreenObject
{
    public:
        Aglutinado(int x, int y, int radius, string file = "");
        ~Aglutinado();
        void Draw(SDL_Renderer* renderer);
        void Render();
        void Update();
        void SetColor(int r, int g, int b, int a = 255);
        void AddTermo(string termo, string file, string posts, SDL_Color cor);
        void AddTermo(string termo, string file, string posts, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        bool IsMouseInside();
        bool IsMouseInsideSector();
    protected:

    private:
        Point center;
        int radius;
        int setorWidth;
        int setorDist;
        SDL_Color color;
        bool colorChange;
        unordered_map<string, Setor*> setores;
        Setor *clicked;
        bool animate;
        bool clockwise;
        Sprite sp;
        bool showWindow;

        int totalTermos;
        void _changeSetorColor(SDL_Renderer *renderer, SDL_Color color);
        void _resetDrawColor(SDL_Renderer *renderer);
};

#endif // AGLUTINADO_H

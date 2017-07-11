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
#define SETOR_WIDTH 20
#define SETOR_DIST 10

using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::pair;

class Aglutinado : public ScreenObject
{
    public:
        Aglutinado(int x, int y, int radius);
        ~Aglutinado();
        void Draw(SDL_Renderer* renderer);
        void Render();
        void Update();
        void SetColor(int r, int g, int b, int a = 255);
        void AddTermo(string termo, SDL_Color cor);
        bool IsMouseInside();
        bool IsMouseInsideSector();
        bool IsMouseInsideSector(string termo);
    protected:

    private:
        Point center;
        int radius;
        int setorWidth;
        int setorDist;
        SDL_Color color;
        bool colorChange;
        unordered_map<string, pair<int, SDL_Color>> termos;
        unordered_map<string, pair<double,double>> angles;
        unordered_map<string, Sprite*> janelasTermo;

        int totalTermos;
        void _changeSetorColor(SDL_Renderer *renderer, SDL_Color color);
        void _resetDrawColor(SDL_Renderer *renderer);
};

#endif // AGLUTINADO_H

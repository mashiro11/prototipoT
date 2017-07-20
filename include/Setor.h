#ifndef SETOR_H
#define SETOR_H

#include <string>
#include "SDL.h"
#include "ScreenObject.h"

#include "Point.h"
#include "Reta.h"
#include "Sprite.h"
#include "InputHandler.h"

#define SETOR_WIDTH 20
#define SETOR_DIST 10

#define PI 3.1415

using std::string;

class Setor: public ScreenObject
{
    public:
        Setor();
        Setor(string termo, Point center, double radius);
        void Render();
        void Update();
        virtual ~Setor();
        void SetColor(SDL_Color color);
        void SetColor(int r, int g, int b, int a);
        void SetPercent(double percent);
        void SetAng(double ang);
        bool IsMouseInside();
        int quantTermos;
        double angS;
        double angF;
        SDL_Color color;
        string termo;

    protected:

    private:
        Point center;
        double percent;
        double setorWidth;
        double setorDist;

        double radius;
        Sprite sp;
};

#endif // SETOR_H

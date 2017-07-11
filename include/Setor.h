#ifndef SETOR_H
#define SETOR_H

#include "SDL.h"
#include "ScreenObject.h"

#include "Point.h"
#include "Reta.h"

#define PI 3.1415

class Setor: public ScreenObject
{
    public:
        Setor();
        Setor(Point center, double radius1, double radius2);
        void Render();
        void Update();
        virtual ~Setor();
        void SetColor(SDL_Color color);
        void SetColor(int r, int g, int b, int a);
        void SetPercent(double percent);
        void SetAng(double ang);
    protected:

    private:
        Point center;
        double percent;
        double angS;
        double angF;

        double radius1;
        double radius2;
        SDL_Color color;
};

#endif // SETOR_H

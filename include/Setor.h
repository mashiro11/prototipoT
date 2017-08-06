#ifndef SETOR_H
#define SETOR_H

#include <string>
#include "SDL.h"
#include "ScreenObject.h"

#include "Point.h"
#include "Reta.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "Text.h"
#include "Window.h"
#include "Aglutinado.h"

#define SETOR_WIDTH 20
#define SETOR_DIST 10
#define ANIMATION_SPEED 0.5


#define PI 3.1415

using std::string;
class Aglutinado;
class Setor: public ScreenObject
{
    public:
        //Setor();
        Setor(Aglutinado &agl, string termo, string file, string posts, Point center, double radius);
        void Render();
        void Draw(SDL_Renderer* renderer);
        void Update();
        void NewAngle(int totalTerms);
        virtual ~Setor();
        void SetColor(SDL_Color color);
        void SetColor(int r, int g, int b, int a);
        void SetPercent(double percent);
        void SetAng(double ang);
        bool IsMouseInside();
        bool IsClicked();
        bool ClickedOut();
        string GetPostPath();
        int quantTermos;
        double angS;
        double angF;
        SDL_Color color;
        string termo;
        void SetAlpha(int alpha);
        static Setor* hasClick;

    protected:

    private:
        Aglutinado &agl;
        void AdjustOpacity();
        void PositionTermbox();
        Sprite termBox;
        Text termSetor;
        bool showTermbox;

        Point center;
        double percent;
        double setorWidth;
        double setorDist;

        double radius;
        Sprite sp;
        string posts;
        int baseAlpha;

        bool hadMouseHover;
};

#endif // SETOR_H

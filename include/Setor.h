#ifndef SETOR_H
#define SETOR_H

#include <string>
#include <set>

#include "SDL.h"
#include "ScreenObject.h"

#include "Point.h"
#include "Reta.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "Text.h"
#include "Window.h"
#include "Aglutinado.h"
#include "Timer.h"

#define SETOR_WIDTH 20
#define SETOR_DIST 10
#define STOP_ANGLE 315

#define ANIMATION_SPEED 7

#define PI 3.1415

using std::string;
using std::set;

class Aglutinado;
class Setor: public ScreenObject
{
    public:
        //Setor();
        Setor(Aglutinado &agl, string termo, string file, string posts);
        void Render();
        void Draw(SDL_Renderer* renderer);
        void Update(float dt);
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
        int angS;
        int angF;
        SDL_Color color;
        string termo;
        void SetAlpha(int alpha);
        static Setor* hasClick;
        void Shrink(float percent);
        static set<Setor*>& GetSetorSet();
        static int setorIncrement;
        void ShowLines();

    protected:

    private:
        Aglutinado &agl;
        void AdjustOpacity();
        void PositionTermbox();
        Sprite termBox;
        Text termSetor;
        bool showTermbox;
        static bool animate;
        static float diff;

        Point center;
        double percent;

        Sprite sp;
        string posts;
        int baseAlpha;

        bool hadMouseHover;
        Timer timer;

        static set<Setor*> setoresTermo;

        static bool showLines;
};

#endif // SETOR_H

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
        virtual ~Setor();

        void Render();
        void Update(float dt);
        void UpdatePosition(float dt);
        void Animate(float dt);
        void NewAngle(int totalTerms);
        void SetAng(double ang);
        void AdjustOpacity();

        Aglutinado& GetAgl();

        void OnClick();
        void OnHover();


        void SelectSetor();
        void UnselectSetor();

        void SetPercent(double percent);
        bool IsMouseInside();
        string GetPostPath();
        int quantTermos;
        int angS;
        int angF;
        string termo;
        void SetAlpha(int alpha);
        void Shrink(float percent);
        void ShowLines();

        static Setor* hasClick;
        static set<Setor*> setoresTermo;
        static set<Setor*>& GetSetorSet();
        static int setorIncrement;

    protected:

    private:
        Aglutinado &agl;
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

        static bool showLines;
};

#endif // SETOR_H

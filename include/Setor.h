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
#define ANIMATION_SPEED 0.5


#define PI 3.1415

using std::string;

class Setor: public ScreenObject
{
    public:
        //Setor();
        Setor(string termo, string file, string posts, Point center, double radius);
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
        string GetPostPath();
        int quantTermos;
        double angS;
        double angF;
        SDL_Color color;
        string termo;


        static void SetCopyAddress(Setor** setor);
        static void SetAnimateAddress(bool* address);
        static void SetAnimationOrientation(bool* clockwise);


    protected:

    private:
        Point center;
        double percent;
        double setorWidth;
        double setorDist;

        double radius;
        Sprite sp;
        string posts;
        static Setor** scopy;
        static bool* animate;
        static bool* clockwise;
        bool showPosts;
};

#endif // SETOR_H

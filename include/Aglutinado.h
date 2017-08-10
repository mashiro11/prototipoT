#ifndef AGLUTINADO_H
#define AGLUTINADO_H

#include <iostream>
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <set>
#include <math.h>
#include <algorithm>

#include "ScreenObject.h"
#include "InputHandler.h"
#include "Setor.h"
#include "Point.h"
//#include "Sprite.h"
#include "DialogBox.h"
#include "Camera.h"

#define PI 3.1415

using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::set;
using std::iter_swap;


class Setor;
class DialogBox;

class Aglutinado : public ScreenObject
{
    public:
        Aglutinado(int x, int y, int radius, string bgFile, string fontFile, int fontSize, TextStyle style);
        ~Aglutinado();
        void Render();
        void Update(float dt);
        void SetColor(int r, int g, int b, int a = 255);
        void AddTermo(string termo, string file, string posts);
        void AddTermo(string termo, int quant);
        void Relaciona(Aglutinado* agl);
        bool IsRelatedTo(Aglutinado* agl);
        void Shrink(float percent);

        bool IsMouseInside();
        bool IsMouseInsideRadius();
        bool IsMouseInsideSector();

        bool IsClicked();
        bool IsAglClicked();
        bool IsSectorClicked();
        void SetAlpha(int alpha);
        Point& GetCenter();
        Point& GetFixedCenter();
        int& GetRadius();
        int GetRadiusExternal();

        static Aglutinado *aglSelected;
        bool selected;
        int setorDist;

        set<Aglutinado*> relacoes;

    protected:

    private:
        void UpdateValues();

        Sprite circle;
        Sprite circleCenter;
        Point center;
        Point centerRelative;
        int radius;
        int setorWidth;
        SDL_Color color;
        bool colorChange;
        bool showRelations;
        bool showCircleCenter;
        unordered_map<string, Setor*> setores;
        bool clockwise;
        DialogBox* dBox;

        int totalTermos;
        void _changeSetorColor(SDL_Renderer *renderer, SDL_Color color);
        void _resetDrawColor(SDL_Renderer *renderer);
        bool showLine;
};

#endif // AGLUTINADO_H

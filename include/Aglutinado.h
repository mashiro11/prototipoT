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

#define ENQUADRAMENTO_X 220*cos(30*PI/180)
#define ENQUADRAMENTO_Y 220*sin(45*PI/180)

using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::set;
using std::iter_swap;


class Setor;
//class DialogBox;

class Aglutinado : public ScreenObject
{
    public:
        Aglutinado(int x, int y, int radius, string fontFile, int fontSize, TextStyle style);
        ~Aglutinado();
        void Render();
        void Update(float dt);
        void LateUpdate();
        void UpdatePositions(float dt);
        void UpdateSectors(float dt);

        void AddTermo(string termo, string file);
        void AddTermo(string termo, int quant);

        void Relaciona(Aglutinado* agl);
        bool IsRelatedTo(Aglutinado* agl);

        void Shrink(float percent);

        bool IsMouseInsideInternalRadius();
        bool IsMouseInsideExternalRadius();
        bool IsMouseInsideSector();

        bool IsOutside();

        void OnClick();
        void OnHover();

        void SetAlpha(int alpha);
        Point& GetCenter();
        Point& GetFixedCenter();
        int& GetRadius();
        int GetRadiusExternal();
        //DialogBox* GetDialogBox();

        void SelectAglutinado();
        void UnselectAglutinado();

        static Aglutinado *aglSelected;
        bool selected;

        bool hasSectorSelected;
        int setorDist;

        set<Aglutinado*> relacoes;
        Point enquadramento;

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
        //DialogBox* dBox;

        int totalTermos;

        //DEBUG
        bool showLine;
        void ShowDebugLines();


};

#endif // AGLUTINADO_H

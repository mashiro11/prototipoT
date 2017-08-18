#ifndef AGLUTINADO_H
#define AGLUTINADO_H

#include <iostream>
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <set>
#include <math.h>
#include <algorithm>
#include <map>
#include <vector>

#include "ScreenObject.h"
#include "InputHandler.h"
#include "Setor.h"
#include "Point.h"
#include "Sprite.h"
#include "DialogBox.h"
#include "Camera.h"
#include "Relacao.h"

#define PI 3.1415

#define ENQUADRAMENTO_X 220*cos(30*PI/180)
#define ENQUADRAMENTO_Y 220*sin(45*PI/180)

#define CIRCULO_EXTERNO_PATH    "img/Setores/circulo.png"
#define CIRCULO_INTERNO_PATH    "img/Setores/circuloCentro.png"

using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::set;
using std::iter_swap;
using std::map;
using std::vector;

class Setor;
class Relacao;
class Aglutinado : public ScreenObject
{
    public:
        Aglutinado(int x, int y, int radius, string fontFile, int fontSize, TextStyle style);
        ~Aglutinado();
        void Render();
        void Update(float dt);
        void LateUpdate();
        void UpdatePositions(float dt);
        void UpdateRelations(float dt);
        void UpdateSectors(float dt);

        void AddTermo(string termo, string file);
        void AddTermo(string termo, int quant);

        void Relaciona(Aglutinado* agl, vector<string> termos, int forca = 1);
        void Relaciona(Aglutinado* agl, Relacao* rel);
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

        void SelectAglutinado();
        void UnselectAglutinado();

        static Aglutinado *aglSelected;
        bool selected;

        bool hasSectorSelected;
        int setorDist;

        map<Aglutinado*, Relacao*> relacoes;
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

        int totalTermos;

        //DEBUG
        bool showLine;
        void ShowDebugLines();


};

#endif // AGLUTINADO_H

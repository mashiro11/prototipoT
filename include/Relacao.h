#ifndef RELACAO_H
#define RELACAO_H

#include <vector>
#include <string>
#include <math.h>

#include "Aglutinado.h"
#include "Text.h"
#include "Window.h"
#include "Sprite.h"

#define PI 3.1415

using std::vector;
using std::string;

class Relacao
{
    public:
        Relacao(Aglutinado& aglut1, Aglutinado& aglut2, int forca = 1);
        virtual ~Relacao();

        void Update(float dt);
        void Render();
        void AddTermo(string termo);
        void PrintTermos();
        void RePosition(Aglutinado* agl);

    protected:

    private:
        Point ptMedio;
        Point posFixed;
        int forca;
        Aglutinado& aglut1;
        Aglutinado& aglut2;
        vector<Text*> termos;
        Sprite *retangulo;
        bool showDebug;
        int i;
};

#endif // RELACAO_H

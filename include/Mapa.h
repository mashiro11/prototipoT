#ifndef MAPA_H
#define MAPA_H

#include <vector>

#include "Aglutinado.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600
#define RAIO 20


using std::vector;

class Mapa
{
    public:
        Mapa();
        virtual ~Mapa();

        void Update();
        void Render();

    protected:

    private:
        Sprite bg;
        vector<Aglutinado*> aglutinados;
        bool reUpdate;

};

#endif // MAPA_H

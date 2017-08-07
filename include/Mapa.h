#ifndef MAPA_H
#define MAPA_H

#include <vector>

#include "Aglutinado.h"
#include "WindowSize.h"

#define RAIO 20


using std::vector;

class Mapa
{
    public:
        Mapa();
        virtual ~Mapa();

        void Update(float dt);
        void Render();

    protected:

    private:
        Sprite bg;
        vector<Aglutinado*> aglutinados;
        bool reUpdate;

};

#endif // MAPA_H

#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <string>

#include "Aglutinado.h"
#include "WindowSize.h"
#include "Text.h"
#include "Window.h"

#define RAIO 20


using std::vector;
using std::to_string;

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
        Text mousePosition;
        Text cameraFocus;
        vector<Aglutinado*> aglutinados;
        bool reUpdate;
        bool showInfo;

};

#endif // MAPA_H

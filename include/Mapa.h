#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <string>

#include "Aglutinado.h"
#include "WindowSize.h"
#include "Text.h"
#include "Window.h"
#include "DialogBox.h"

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

        void OnHover();

    protected:

    private:
        Sprite bg;
        Sprite busca;
        Sprite compartilhar;
        Sprite calendario;
        Sprite meEncontrar;
        Sprite zoomIn;
        Sprite zoomOut;

        Text buscaH;
        Text compartilharH;
        Text calendarioH;
        Text meEncontrarH;
        Text zoomInH;
        Text zoomOutH;

        bool showBusca;
        bool showCompartilhar;
        bool showCalendario;
        bool showMeEncontrar;
        bool showZoomIn;
        bool showZoomOut;


        Text mousePosition;
        Text cameraFocus;
        vector<Aglutinado*> aglutinados;
        bool showInfo;
};

#endif // MAPA_H

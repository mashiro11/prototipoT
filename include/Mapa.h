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
using std::pair;
using std::make_pair;

class Mapa
{
    public:
        Mapa();
        virtual ~Mapa();

        void Update(float dt);
        void Render();
        void SetButtons();

    protected:

    private:
        Sprite bg;
        Text mousePosition;
        Text cameraFocus;
        vector<Aglutinado*> aglutinados;
        bool showInfo;
        vector<pair<Sprite*, Text*>> botoes;
};

#endif // MAPA_H

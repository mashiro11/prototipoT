#ifndef RELACAO_H
#define RELACAO_H

#include <vector>
#include <string>

#include "Aglutinado.h"
#include "Text.h"

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

    protected:

    private:
        Point pt;
        int forca;
        Aglutinado& aglut1;
        Aglutinado& aglut2;
        vector<Text*> termos;
};

#endif // RELACAO_H

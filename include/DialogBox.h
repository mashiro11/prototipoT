#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include "Sprite.h"
#include "Text.h"

#define BUTTON_BACK_PATH "img/Botoes/Topogramas_Botao_Recuar_1.png"
#define BUTTON_NEXT_PATH "img/Botoes/Topogramas_Botao_Avancar_1.png"

#define SCROLL_SPEED 3

class DialogBox
{
    public:
        DialogBox(int x, int y, string bgFile, string fontFile, int fontSize, TextStyle style);
        virtual ~DialogBox();

        void Render();
        void Update();
        void SetTermo(string termo);
        void SetPost(string post, int x = 0, int y = 0);
        void RemovePost();
        int GetWidth();
        void CentralizeText(Text text);
        bool IsMouseInside();

        bool showDBox;
        bool showPosts;
        string termoTemp;
        string termoSelected;

    protected:

    private:
        Sprite body;
        Sprite buttonBack;
        Sprite buttonNext;
        Text termo;
        Text verPosts;
        Sprite* post;
};

#endif // DIALOGBOX_H

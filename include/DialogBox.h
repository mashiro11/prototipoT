#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include <string>

#include "Sprite.h"
#include "Text.h"
#include "Aglutinado.h"
#include "Setor.h"

#define WINDOW_BOX_PATH     "img/janela.png"
#define BUTTON_BACK_PATH    "img/Botoes/Topogramas_Botao_Recuar_1.png"
#define BUTTON_NEXT_PATH    "img/Botoes/Topogramas_Botao_Avancar_1.png"

#define SCROLL_SPEED 3

using std::string;
using std::to_string;

class Aglutinado;
class DialogBox
{
    public:
        virtual ~DialogBox();

        void Render();
        void Update(float dt);
        void LateUpdate();
        void UpdatePosition(float dt);

        void OnClick();
        void OnHover();
        void OnMouseRoll();
        void SetPostTab();
        void SetTabColor();


        void Open();
        void ChangeTermo();
        void Close();
        void SetTermo();
        void SetQuantSetores();
        void SetPost(string post, int x = 0, int y = 0);
        void RemovePost();
        int GetWidth();
        void CentralizeText(Text text);
        bool IsMouseInside();
        static DialogBox& GetInstance();

        static bool showDBox;
        static bool showPosts;
        string termoTemp;
        string termoSelected;
        static bool transfer;

    protected:

    private:
        DialogBox();//int x, int y, string fontFile, int fontSize, TextStyle style);
        //Aglutinado& agl;
        Point posRel;
        Sprite body;
        Sprite buttonBack;
        Sprite buttonNext;
        Text termo;
        Text verPosts;
        Text quantSetores;
        unsigned int numSetores;
        Sprite* post;
        static DialogBox* instance;
        Aglutinado* first;
        int counter;
        Text facebook;
        Text instagram;
        Text topogramas;
        Text twitter;
        SDL_Color color;
        SDL_Color defaultTabColor;

        typedef enum{
            FACEBOOK = 0,
            INSTAGRAM,
            TWITTER,
            TOPOGRAMAS,
            NONE
        }PostSelected;

        PostSelected tab;
        PostSelected lastTab;
};

#endif // DIALOGBOX_H

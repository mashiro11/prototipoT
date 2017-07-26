#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include "Sprite.h"
#include "Text.h"

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

    protected:

    private:
        Sprite body;
        Text termo;
        Text verPosts;
        Sprite* post;
};

#endif // DIALOGBOX_H

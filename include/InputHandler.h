#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>
#include <iostream>

using std::cout;
using std::endl;

typedef enum{
    NO_MOUSE_EVENT = 0,
    MOUSE_LBUTTON_PRESSED,
    MOUSE_LBUTTON_RELEASED,
}MOUSE_LB_STATE;

class InputHandler
{
    public:
        static MOUSE_LB_STATE GetMouseLBState();
        static int GetMouseX();
        static int GetMouseY();
        static int GetKey();
        static bool QuitRequested();

        static void Update();

    protected:

    private:
        static MOUSE_LB_STATE mouseLButton;
        static SDL_KeyboardEvent *keyboardState;
        static bool keydown;
        static bool quitRequested;
};

#endif // INPUTHANDLER_H

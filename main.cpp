#include <iostream>
#include <SDL.h>
#include <vector>

#include "Window.h"
#include "Mapa.h"
#include "InputHandler.h"
#include "Camera.h"

#define TITULO "Topograma"

using std::vector;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char** argv)
{
    int winOp = Window::Start(TITULO);
    if(winOp != 0 ){
        cout << "Closing aplication..." << endl;
        return winOp;
    }
    Mapa mapa;
    float time = SDL_GetTicks();
    while(!InputHandler::QuitRequested()){
        float pastFrameStart = time;
        time = SDL_GetTicks();
        float dt = (time - pastFrameStart)/1000;

        InputHandler::Update(dt);
        Camera::Update(dt);

        mapa.Update(dt);

        mapa.Render();
        Window::Render();
    }
    Window::Finish();
    return 0;
}

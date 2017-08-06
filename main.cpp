#include <iostream>
#include <SDL.h>
#include <vector>

#include "Window.h"
#include "Mapa.h"
#include "InputHandler.h"
#include "Camera.h"

#define TITULO "Topograma"

using std::vector;
int main(int argc, char** argv)
{
    int winOp = Window::Start(TITULO);
    if(winOp != 0 ){
        cout << "Closing aplication..." << endl;
        return winOp;
    }
    Mapa mapa;
    while(!InputHandler::QuitRequested()){
        InputHandler::Update();
        Camera::Update();

        mapa.Update();

        mapa.Render();
        Window::Render();
    }
    Window::Finish();
    return 0;
}

#include <iostream>
#include <SDL.h>

#include "Window.h"
#include "Aglutinado.h"
#include "InputHandler.h"

#define TITULO "Topograma"
#define RAIO 80
int main(int argc, char** argv)
{
    int winOp = Window::Start(TITULO);
    if(winOp != 0 ){
        cout << "Closing aplication..." << endl;
        return winOp;
    }

    Aglutinado bola(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, RAIO);
    bola.SetColor(255, 0, 0);
    bola.AddTermo("engarrafamento", 0,0,255, 255);
    bola.AddTermo("parque", 0, 255, 0, 255);
    bola.AddTermo("parque", 0, 255, 0, 100);
    bola.AddTermo("panqueca", 0, 50, 50, 100);

    Sprite bg("img/bg.PNG");
    bg.Resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    bg.Render();

    bola.Draw(Window::GetRenderer());

    while(!InputHandler::QuitRequested()){
        InputHandler::Update();
        bola.Update();
        Window::Render();
    }
    Window::Finish();
    return 0;
}

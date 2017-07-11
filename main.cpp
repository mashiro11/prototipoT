#include <iostream>
#include <SDL.h>

#include "Window.h"
#include "Aglutinado.h"
#include "InputHandler.h"

#define TITULO "Topograma"
#define RAIO 80
int main(int argc, char** argv)
{
    Window::Start(TITULO);
    Aglutinado bola(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, RAIO);
    bola.SetColor(255, 0, 0);
    SDL_Color cor = {0, 0, 255, 255};
    bola.AddTermo("engarrafamento", cor);
    cor = {0, 255, 0, 255};
    bola.AddTermo("parque", cor);
    bola.AddTermo("parque", cor);
    Sprite bg("img/bg.PNG");
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

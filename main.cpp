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


    Sprite bg("img/bg.PNG");
    bg.Resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    Aglutinado bola(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, RAIO, "img/janela.png");
    bola.SetColor(255, 0, 0);
    bola.AddTermo("engarrafamento", "img/termotriste.png", "img/text.png", 0, 0, 255, 255);
    bola.AddTermo("parque", "img/termofeliz.png", "img/text2.png", 0, 255, 0, 255);
    bola.AddTermo("parque", "img/termofeliz.png", "img/text2.png", 0, 255, 0, 100);
    bola.AddTermo("panqueca", "img/hashtagfeliz.png", "img/text3.png", 0, 50, 50, 100);

    while(!InputHandler::QuitRequested()){
        InputHandler::Update();
        bola.Update();
        bg.Render();

        SDL_RenderDrawLine(Window::GetRenderer(), 0, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT/2);
        SDL_RenderDrawLine(Window::GetRenderer(), WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT);

        bola.Render();
        Window::Render();
    }
    Window::Finish();
    return 0;
}

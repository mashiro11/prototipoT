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


    Sprite bg("img/Mapa/Topogramas_Mapa1.png");
    bg.Resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    Aglutinado bola(WINDOW_WIDTH/4, WINDOW_HEIGHT/4, RAIO, "img/janela.png", "fonts/Roboto-Bold.ttf", 20, BLENDED);
    bola.SetColor(255, 0, 0);
    bola.AddTermo("#fogo", "img/hashtagfeliz.png", "img/Posts/HashtagsFelizes/Fogo1/#Fogo-Facebook1.png", 0, 0, 255, 255);
    bola.AddTermo("chuva", "img/termofeliz.png", "img/Posts/Termos Felizes/Chuva 1/Chuva_Twitter_1.png", 0, 255, 0, 255);
    bola.AddTermo("engarrafamento", "img/termotriste.png", "img/Posts/Termos Tristes/Engarrafamento 1/Engarrafamento_Twitter_1.png", 0, 255, 0, 100);
    bola.AddTermo("correr", "img/termofeliz.png", "img/Posts/Termos Felizes/Correr 1/Correr_Twitter_11.png", 0, 50, 50, 100);

    bola.AddTermo("chuva", 10);
    bola.AddTermo("#fogo", 5);
    bola.AddTermo("correr", 3);
    bola.AddTermo("engarrafamento", 7 );

    while(!InputHandler::QuitRequested()){
        InputHandler::Update();
        bola.Update();
        bg.Render();

        SDL_RenderDrawLine(Window::GetRenderer(), 0, WINDOW_HEIGHT/4, WINDOW_WIDTH, WINDOW_HEIGHT/4);
        SDL_RenderDrawLine(Window::GetRenderer(), WINDOW_WIDTH/4, 0, WINDOW_WIDTH/4, WINDOW_HEIGHT);

        bola.Render();
        Window::Render();
    }
    Window::Finish();
    return 0;
}

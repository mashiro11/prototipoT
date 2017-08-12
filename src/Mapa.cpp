#include "Mapa.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
#endif //DEBUG

Mapa::Mapa():
    bg("img/Mapa/Topogramas_Mapa1.png"),
    reUpdate(false),
    mousePosition("fonts/Roboto-Bold.ttf", 10, BLENDED, "x", 0, 0, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    cameraFocus("fonts/Roboto-Bold.ttf", 10, BLENDED, "x", 0, 15, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    showInfo(false)
{
    bg.Resize(WINDOW_WIDTH*3, WINDOW_HEIGHT*3);
    bg.SetPosition(-WINDOW_WIDTH, -WINDOW_HEIGHT);

    //Primeiro
    Aglutinado *ag1 = new Aglutinado(WINDOW_WIDTH/4, WINDOW_HEIGHT/4, RAIO, "img/janela.png", "fonts/Roboto-Bold.ttf", 20, BLENDED);
    aglutinados.push_back(ag1);
    aglutinados.back()->AddTermo("#fogo", "hashtagfeliz", "#Fogo-Facebook1");
    aglutinados.back()->AddTermo("chuva", "termofeliz", "Chuva_Twitter_11");
    aglutinados.back()->AddTermo("engarrafamento", "termotriste", "Engarrafamento_Twitter_11");
    aglutinados.back()->AddTermo("correr", "termofeliz", "Correr_Twitter_11");

    aglutinados.back()->AddTermo("chuva", 10);
    aglutinados.back()->AddTermo("#fogo", 5);
    aglutinados.back()->AddTermo("correr", 3);
    aglutinados.back()->AddTermo("engarrafamento", 7 );

    //Segundo
    //Aglutinado *ag1 = ;
    aglutinados.push_back(new Aglutinado(WINDOW_WIDTH* 3/4.0, WINDOW_HEIGHT* 3/4.0, RAIO, "img/janela.png", "fonts/Roboto-Bold.ttf", 20, BLENDED));
    aglutinados.back()->AddTermo("#fogo", "hashtagfeliz", "#Fogo-Facebook1");
    aglutinados.back()->AddTermo("chuva", "termofeliz", "Chuva_Twitter_11");
    aglutinados.back()->AddTermo("engarrafamento", "termotriste", "Engarrafamento_Twitter_11");
    aglutinados.back()->AddTermo("correr", "termofeliz", "Correr_Twitter_11");

    aglutinados.back()->AddTermo("chuva", 3);
    aglutinados.back()->AddTermo("#fogo", 8);
    aglutinados.back()->AddTermo("correr", 5);
    aglutinados.back()->AddTermo("engarrafamento", 11 );
    aglutinados.back()->Relaciona(ag1);

    //Terceiro
    aglutinados.push_back(new Aglutinado(WINDOW_WIDTH* 1/4.0, WINDOW_HEIGHT* 3/4.0, RAIO, "img/janela.png", "fonts/Roboto-Bold.ttf", 20, BLENDED));
    aglutinados.back()->AddTermo("#fogo", "hashtagfeliz", "#Fogo-Facebook1");
    aglutinados.back()->AddTermo("chuva", "termofeliz", "Chuva_Twitter_11");
    aglutinados.back()->AddTermo("engarrafamento", "termotriste", "Engarrafamento_Twitter_11");
    aglutinados.back()->AddTermo("correr", "termofeliz", "Correr_Twitter_11");
    aglutinados.back()->AddTermo("netflix", "termofeliz", "Correr_Twitter_11");

    aglutinados.back()->AddTermo("chuva", 2);
    aglutinados.back()->AddTermo("#fogo", 8);
    aglutinados.back()->AddTermo("correr", 9);
    aglutinados.back()->AddTermo("engarrafamento", 3 );
    aglutinados.back()->AddTermo("netflix", 5 );
    aglutinados.back()->Relaciona(ag1);

    aglutinados.back()->Shrink(0.5);

}

Mapa::~Mapa()
{
    //dtor
}

void Mapa::Update(float dt){
    if(Camera::cameraMove){
        bg.SetPosition(-WINDOW_WIDTH-Camera::position.x, -WINDOW_HEIGHT-Camera::position.y);
    }

    //Aqui verifica-se se algum Aglutinado foi clicado.
    //Caso negativo, aglSelected, que contem o endereço do aglutinado clicado
    //recebe nullpointer.
    //Se nenhum aglutinado está selecionado, significa que nenhum setor está selecionado.
    //O aglutinado não pode colocar o hasClick do setor em nullpointer uma vez que o aglutinado
    //conhece apenas os seus proprios setores.;
    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        (*it)->Update(dt);
    }

    if(!Aglutinado::selected){
        Aglutinado::aglSelected = nullptr;
        Setor::hasClick = nullptr;
    }

    //DEBUG
    if(InputHandler::GetKey() == SDLK_0){
        showInfo = !showInfo;
    }
    if(showInfo && InputHandler::mouseMoved){
        mousePosition.SetText(to_string((int)(InputHandler::GetMousePosition().x + Camera::position.x))+"x"
                              +to_string((int)(InputHandler::GetMousePosition().y + Camera::position.y)));
        mousePosition.SetPos(InputHandler::GetMousePosition().x, InputHandler::GetMousePosition().y-10);
        cameraFocus.SetText(to_string(Camera::GetFollow().x)+"x"+to_string(Camera::GetFollow().y));
    }
}

void Mapa::Render(){
    bg.Render();
    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        (*it)->Render();
    }

    //DEBUG
    if(showInfo){
        mousePosition.Render();
        cameraFocus.Render();

        SDL_SetRenderDrawColor(Window::GetRenderer(), 100, 100, 0, 255);
        //linha vertical
        SDL_RenderDrawLine(Window::GetRenderer(),
                           InputHandler::GetMousePosition().x, 0,
                           InputHandler::GetMousePosition().x, WINDOW_HEIGHT);
        //Linha horizontal
        SDL_RenderDrawLine(Window::GetRenderer(),
                           0, InputHandler::GetMousePosition().y,
                           WINDOW_WIDTH, InputHandler::GetMousePosition().y);
    }
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

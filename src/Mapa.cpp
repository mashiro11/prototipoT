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
    showMousePosition(false)
{
    bg.Resize(WINDOW_WIDTH, WINDOW_HEIGHT);

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
    bool aglClicked = false;
    bg.SetPosition(Camera::position.x, Camera::position.y);
    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        (*it)->Update(dt);
        aglClicked |= (*it)->selected;
    }
    if(aglClicked == false){
        Aglutinado::aglSelected = nullptr;
        Setor::hasClick = nullptr;
    }

    //DEBUG
    if(InputHandler::GetKey() == SDLK_0){
        showMousePosition = !showMousePosition;
    }

    if(showMousePosition){
        mousePosition.SetText(to_string(InputHandler::GetMouseX())+"x"+to_string(InputHandler::GetMouseY()));
    }
}

void Mapa::Render(){
    bg.Render();
    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        (*it)->Render();
    }
    //DEBUG
    if(showMousePosition){
        mousePosition.Render();
    }
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

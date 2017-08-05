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
    reUpdate(false)
{
    bg.Resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    aglutinados.push_back(new Aglutinado(WINDOW_WIDTH/4, WINDOW_HEIGHT/4, RAIO, "img/janela.png", "fonts/Roboto-Bold.ttf", 20, BLENDED));
    aglutinados.back()->AddTermo("#fogo", "img/Setores/hashtagfeliz72.png", "img/Posts/HashtagsFelizes/Fogo1/#Fogo-Facebook1.png", 0, 0, 255, 255);
    aglutinados.back()->AddTermo("chuva", "img/Setores/termofeliz72.png", "img/Posts/Termos Felizes/Chuva 1/Chuva_Twitter_11.png", 0, 255, 0, 255);
    aglutinados.back()->AddTermo("engarrafamento", "img/Setores/termotriste72.png", "img/Posts/Termos Tristes/Engarrafamento 1/Engarrafamento_Twitter_11.png", 0, 255, 0, 100);
    aglutinados.back()->AddTermo("correr", "img/Setores/termofeliz72.png", "img/Posts/Termos Felizes/Correr 1/Correr_Twitter_11.png", 0, 50, 50, 100);

    aglutinados.back()->AddTermo("chuva", 10);
    aglutinados.back()->AddTermo("#fogo", 5);
    aglutinados.back()->AddTermo("correr", 3);
    aglutinados.back()->AddTermo("engarrafamento", 7 );

    aglutinados.push_back(new Aglutinado(WINDOW_WIDTH* 3/4.0, WINDOW_HEIGHT* 3/4.0, RAIO, "img/janela.png", "fonts/Roboto-Bold.ttf", 20, BLENDED));
    aglutinados.back()->AddTermo("#fogo", "img/Setores/hashtagfeliz72.png", "img/Posts/HashtagsFelizes/Fogo1/#Fogo-Facebook1.png", 0, 0, 255, 255);
    aglutinados.back()->AddTermo("chuva", "img/Setores/termofeliz72.png", "img/Posts/Termos Felizes/Chuva 1/Chuva_Twitter_11.png", 0, 255, 0, 255);
    aglutinados.back()->AddTermo("engarrafamento", "img/Setores/termotriste72.png", "img/Posts/Termos Tristes/Engarrafamento 1/Engarrafamento_Twitter_11.png", 0, 255, 0, 100);
    aglutinados.back()->AddTermo("correr", "img/Setores/termofeliz72.png", "img/Posts/Termos Felizes/Correr 1/Correr_Twitter_11.png", 0, 50, 50, 100);

    aglutinados.back()->AddTermo("chuva", 10);
    aglutinados.back()->AddTermo("#fogo", 5);
    aglutinados.back()->AddTermo("correr", 3);
    aglutinados.back()->AddTermo("engarrafamento", 7 );

}

Mapa::~Mapa()
{
    //dtor
}

void Mapa::Update(){
    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        (*it)->Update();
    }
}

void Mapa::Render(){
    bg.Render();
    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        (*it)->Render();
    }
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

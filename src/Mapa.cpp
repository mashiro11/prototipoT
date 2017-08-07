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

    //Primeiro
    Aglutinado *ag1 = new Aglutinado(WINDOW_WIDTH/4, WINDOW_HEIGHT/4, RAIO, "img/janela.png", "fonts/Roboto-Bold.ttf", 20, BLENDED);
    aglutinados.push_back(ag1);
    aglutinados.back()->AddTermo("#fogo", "img/Setores/hashtagfeliz300.png", "img/Posts/HashtagsFelizes/Fogo1/#Fogo-Facebook1.png", 0, 0, 255, 255);
    aglutinados.back()->AddTermo("chuva", "img/Setores/termofeliz300.png", "img/Posts/Termos Felizes/Chuva 1/Chuva_Twitter_11.png", 0, 255, 0, 255);
    aglutinados.back()->AddTermo("engarrafamento", "img/Setores/termotriste300.png", "img/Posts/Termos Tristes/Engarrafamento 1/Engarrafamento_Twitter_11.png", 0, 255, 0, 100);
    aglutinados.back()->AddTermo("correr", "img/Setores/termofeliz300.png", "img/Posts/Termos Felizes/Correr 1/Correr_Twitter_11.png", 0, 50, 50, 100);

    aglutinados.back()->AddTermo("chuva", 10);
    aglutinados.back()->AddTermo("#fogo", 5);
    aglutinados.back()->AddTermo("correr", 3);
    aglutinados.back()->AddTermo("engarrafamento", 7 );

    //Segundo
    //Aglutinado *ag1 = ;
    aglutinados.push_back(new Aglutinado(WINDOW_WIDTH* 3/4.0, WINDOW_HEIGHT* 3/4.0, RAIO, "img/janela.png", "fonts/Roboto-Bold.ttf", 20, BLENDED));
    aglutinados.back()->AddTermo("#fogo", "img/Setores/hashtagfeliz300.png", "img/Posts/HashtagsFelizes/Fogo1/#Fogo-Facebook1.png", 0, 0, 255, 255);
    aglutinados.back()->AddTermo("chuva", "img/Setores/termofeliz300.png", "img/Posts/Termos Felizes/Chuva 1/Chuva_Twitter_11.png", 0, 255, 0, 255);
    aglutinados.back()->AddTermo("engarrafamento", "img/Setores/termotriste300.png", "img/Posts/Termos Tristes/Engarrafamento 1/Engarrafamento_Twitter_11.png", 0, 255, 0, 100);
    aglutinados.back()->AddTermo("correr", "img/Setores/termofeliz300.png", "img/Posts/Termos Felizes/Correr 1/Correr_Twitter_11.png", 0, 50, 50, 100);

    aglutinados.back()->AddTermo("chuva", 3);
    aglutinados.back()->AddTermo("#fogo", 8);
    aglutinados.back()->AddTermo("correr", 5);
    aglutinados.back()->AddTermo("engarrafamento", 11 );
    aglutinados.back()->Relaciona( ag1 );

    //Terceiro
    aglutinados.push_back(new Aglutinado(WINDOW_WIDTH* 1/4.0, WINDOW_HEIGHT* 3/4.0, RAIO, "img/janela.png", "fonts/Roboto-Bold.ttf", 20, BLENDED));
    aglutinados.back()->AddTermo("#fogo", "img/Setores/hashtagfeliz300.png", "img/Posts/HashtagsFelizes/Fogo1/#Fogo-Facebook1.png", 0, 0, 255, 255);
    aglutinados.back()->AddTermo("chuva", "img/Setores/termofeliz300.png", "img/Posts/Termos Felizes/Chuva 1/Chuva_Twitter_11.png", 0, 255, 0, 255);
    aglutinados.back()->AddTermo("engarrafamento", "img/Setores/termotriste300.png", "img/Posts/Termos Tristes/Engarrafamento 1/Engarrafamento_Twitter_11.png", 0, 255, 0, 100);
    aglutinados.back()->AddTermo("correr", "img/Setores/termofeliz300.png", "img/Posts/Termos Felizes/Correr 1/Correr_Twitter_11.png", 0, 50, 50, 100);
    aglutinados.back()->AddTermo("netflix", "img/Setores/termofeliz300.png", "img/Posts/Termos Felizes/Correr 1/Correr_Twitter_11.png", 0, 50, 50, 100);

    aglutinados.back()->AddTermo("chuva", 2);
    aglutinados.back()->AddTermo("#fogo", 8);
    aglutinados.back()->AddTermo("correr", 9);
    aglutinados.back()->AddTermo("engarrafamento", 3 );
    aglutinados.back()->AddTermo("netflix", 5 );
    aglutinados.back()->Relaciona(ag1);

}

Mapa::~Mapa()
{
    //dtor
}

void Mapa::Update(float dt){
    bool aglClicked = false;
    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        (*it)->Update(dt);
        aglClicked |= (*it)->selected;
    }
    if(aglClicked == false){
        Aglutinado::aglSelected = nullptr;
        Setor::hasClick = nullptr;
    }
//    bg.SetX( bg.GetX() + Camera::position.x);
//    bg.SetY( bg.GetY() + Camera::position.y);
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

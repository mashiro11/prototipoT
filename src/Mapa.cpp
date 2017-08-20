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
    mousePosition("fonts/Roboto-Bold.ttf", 10, BLENDED, "x", 0, 0, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    cameraFocus("fonts/Roboto-Bold.ttf", 10, BLENDED, "x", 0, 15, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    showInfo(false)
    //dBox(radius + 20 + 10 + 10,- radius - 20 - 10, fontFile, fontSize, style);
{
    bg.Resize(WINDOW_WIDTH*3, WINDOW_HEIGHT*3);
    bg.SetPosition(-WINDOW_WIDTH, -WINDOW_HEIGHT);

    //Primeiro
    Aglutinado *ag1 = new Aglutinado(WINDOW_WIDTH/4, WINDOW_HEIGHT/4, RAIO, "fonts/Roboto-Bold.ttf", 20, BLENDED);
    aglutinados.push_back(ag1);
    aglutinados.back()->AddTermo("#fogo", "hashtagfeliz");
    aglutinados.back()->AddTermo("chuva", "termofeliz");
    aglutinados.back()->AddTermo("engarrafamento", "termotriste");
    aglutinados.back()->AddTermo("correr", "termofeliz");

    aglutinados.back()->AddTermo("chuva", 10);
    aglutinados.back()->AddTermo("#fogo", 5);
    aglutinados.back()->AddTermo("correr", 3);
    aglutinados.back()->AddTermo("engarrafamento", 7 );

    //Segundo
    //Aglutinado *ag1 = ;
    aglutinados.push_back(new Aglutinado(WINDOW_WIDTH* 3/4.0, WINDOW_HEIGHT* 3/4.0, RAIO, "fonts/Roboto-Bold.ttf", 20, BLENDED));
    aglutinados.back()->AddTermo("#fogo", "hashtagfeliz");
    aglutinados.back()->AddTermo("chuva", "termofeliz");
    aglutinados.back()->AddTermo("engarrafamento", "termotriste");
    aglutinados.back()->AddTermo("correr", "termofeliz");

    aglutinados.back()->AddTermo("chuva", 3);
    aglutinados.back()->AddTermo("#fogo", 8);
    aglutinados.back()->AddTermo("correr", 5);
    aglutinados.back()->AddTermo("engarrafamento", 11 );
    vector<string> termos1;
    termos1.push_back("engarrafamento");
    termos1.push_back("cigarro");
    termos1.push_back("correr");
    aglutinados.back()->Relaciona(ag1, termos1, 2);

    //Terceiro
    aglutinados.push_back(new Aglutinado(WINDOW_WIDTH* 1/4.0, WINDOW_HEIGHT* 3/4.0, RAIO, "fonts/Roboto-Bold.ttf", 20, BLENDED));
    aglutinados.back()->AddTermo("#fogo", "hashtagfeliz");
    aglutinados.back()->AddTermo("chuva", "termofeliz");
    aglutinados.back()->AddTermo("engarrafamento", "termotriste");
    aglutinados.back()->AddTermo("correr", "termofeliz");
    //aglutinados.back()->AddTermo("netflix", "termofeliz", "Correr");

    aglutinados.back()->AddTermo("chuva", 2);
    aglutinados.back()->AddTermo("#fogo", 8);
    aglutinados.back()->AddTermo("correr", 9);
    aglutinados.back()->AddTermo("engarrafamento", 3 );
    //aglutinados.back()->AddTermo("netflix", 5 );
    vector<string> termos2;
    termos2.push_back("netflix");
    termos2.push_back("#fogo");
    termos2.push_back("correr");
    aglutinados.back()->Relaciona(ag1, termos2, 3);

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
    //É feito update de todos os aglutinados
    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        (*it)->Update(dt);
    }

    //verifica-se se algum deles está selecionado
    bool aglSelected = false;
    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        if((*it)->selected){
            aglSelected = true;
            break;
        }
    }

    //Se nenhum estiver selecionado, limpa os ponteiros
    if(!aglSelected){
        Aglutinado::aglSelected = nullptr;
        Setor::hasClick = nullptr;
    }

    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        (*it)->LateUpdate();
    }
    //if(Aglutinado::aglSelected != nullptr){
        DialogBox::GetInstance().Update(dt);
        DialogBox::GetInstance().LateUpdate();
    //}


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
    DialogBox::GetInstance().Render();

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

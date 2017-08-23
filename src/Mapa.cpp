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
    bg("img/Mapa/Topogramas_Mapa12.png"),
    mousePosition("fonts/Roboto-Bold.ttf", 10, BLENDED, "x", 0, 0, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    cameraFocus("fonts/Roboto-Bold.ttf", 10, BLENDED, "x", 0, 15, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    showInfo(false)
    //dBox(radius + 20 + 10 + 10,- radius - 20 - 10, fontFile, fontSize, style);
{
    //bg.Resize(WINDOW_WIDTH*1.5, WINDOW_HEIGHT*1.5);
    bg.SetPosition(-(BG_WIDTH - WINDOW_WIDTH)/2, -(BG_HEIGHT - WINDOW_HEIGHT)/2);
    SetButtons();

    /***********
        termos possiveis:

            hashtagfeliz
                #Feliz
                #Ferias
                #fogo

            hashtagtriste
                #Chateado1
                #Chateado2

            termofeliz
                Animada
                chuva
                correr
                Ferias
                Frio

            termotriste
                Acidente
                Acidente2
                engarrafamento
                Frio

    ***********/

    //Primeiro
    Aglutinado *ag1 = new Aglutinado(WINDOW_WIDTH/4, WINDOW_HEIGHT/4, RAIO, "fonts/Roboto-Bold.ttf", 20, BLENDED);
    aglutinados.push_back(ag1);
    aglutinados.back()->AddTermo("#fogo", "hashtagfeliz");
    aglutinados.back()->AddTermo("engarrafamento", "termotriste");
    aglutinados.back()->AddTermo("correr", "termofeliz");

    aglutinados.back()->AddTermo("#fogo", 5);
    aglutinados.back()->AddTermo("correr", 3);
    aglutinados.back()->AddTermo("engarrafamento", 7 );
    aglutinados.back()->Shrink(1.2);


    //Segundo
    //Aglutinado *ag1 = ;
    aglutinados.push_back(new Aglutinado(WINDOW_WIDTH* 3/4.0, WINDOW_HEIGHT* 3/4.0, RAIO, "fonts/Roboto-Bold.ttf", 20, BLENDED));
    aglutinados.back()->AddTermo("chuva", "termofeliz");
    aglutinados.back()->AddTermo("engarrafamento", "termotriste");
    aglutinados.back()->AddTermo("Animada", "termofeliz");

    aglutinados.back()->AddTermo("chuva", 3);
    aglutinados.back()->AddTermo("Animada", 5);
    aglutinados.back()->AddTermo("engarrafamento", 11 );
    vector<string> termos1;
    termos1.push_back("engarrafamento");
    termos1.push_back("#tenso");
    aglutinados.back()->Relaciona(ag1, termos1, 2);
    aglutinados.back()->Shrink(0.8);

    //Terceiro
    Aglutinado* agl3 = new Aglutinado(WINDOW_WIDTH* 1/4.0, WINDOW_HEIGHT* 3/4.0, RAIO, "fonts/Roboto-Bold.ttf", 20, BLENDED);
    aglutinados.push_back(agl3);
    aglutinados.back()->AddTermo("Ferias", "termofeliz");
    aglutinados.back()->AddTermo("Frio", "termofeliz");
    aglutinados.back()->AddTermo("#fogo", "hashtagfeliz");

    aglutinados.back()->AddTermo("Ferias", 2);
    aglutinados.back()->AddTermo("Frio", 8);
    aglutinados.back()->AddTermo("#fogo", 9);

    vector<string> termos2;
    termos2.push_back("netflix");
    termos2.push_back("#fogo");
    termos2.push_back("Ferias");
    aglutinados.back()->Relaciona(ag1, termos2, 3);
    aglutinados.back()->Shrink(0.6);

    //Quarto
    aglutinados.push_back(new Aglutinado(500, 60, RAIO, "fonts/Roboto-Bold.ttf", 20, BLENDED));
    aglutinados.back()->AddTermo("Frio", "termotriste");
    aglutinados.back()->AddTermo("#Chateado1", "hashtagtriste");

    aglutinados.back()->AddTermo("Frio", 9);
    aglutinados.back()->AddTermo("#Chateado1", 3 );

    vector<string> termos3;
    termos3.push_back("Frio");
    termos3.push_back("gripe");
    aglutinados.back()->Relaciona(agl3, termos3, 2);
    aglutinados.back()->Shrink(0.9);
}

Mapa::~Mapa()
{
    //dtor
}

void Mapa::Update(float dt){
    if(Camera::cameraMove){
        bg.SetPosition(-(BG_WIDTH - WINDOW_WIDTH)/2-Camera::position.x,
                       -(BG_HEIGHT - WINDOW_HEIGHT)/2-Camera::position.y);
        //bg.SetPosition(-WINDOW_WIDTH/4-Camera::position.x, -WINDOW_HEIGHT/4-Camera::position.y);
        //bg.SetPosition(-Camera::position.x, -Camera::position.y);
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
    for(unsigned int i = 0; i < botoes.size(); i++){
        botoes[i].first->Render();
        if(botoes[i].first->IsMouseInside()){
            botoes[i].second->Render();
        }
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

void Mapa::SetButtons(){
    Sprite* button = new Sprite("img/Botoes/calendario.png", WINDOW_WIDTH - 103 - 5, 5);
    Text* hoverText = new Text("fonts/Roboto-Bold.ttf", 10, BLENDED, "calendario", 0, 0, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE);
    hoverText->SetPos(button->GetX() - hoverText->GetWidth() - 2, button->GetY());
    botoes.push_back(make_pair(button, hoverText));

    button = new Sprite("img/Botoes/buscar.png", WINDOW_WIDTH - 22 - 5, button->GetY() + button->GetHeight() + 5);
    hoverText = new Text("fonts/Roboto-Bold.ttf", 10, BLENDED, "buscar", 0, 0, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE);
    hoverText->SetPos(button->GetX() - hoverText->GetWidth() - 2, button->GetY());
    botoes.push_back(make_pair(button, hoverText));

    button = new Sprite("img/Botoes/localizar.png", WINDOW_WIDTH - 22 - 5, button->GetY() + button->GetHeight() + 5);
    hoverText = new Text("fonts/Roboto-Bold.ttf", 10, BLENDED, "localizar", 0, 0, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE);
    hoverText->SetPos(button->GetX() - hoverText->GetWidth() - 2, button->GetY());
    botoes.push_back(make_pair(button, hoverText));

    button = new Sprite("img/Botoes/compartilhar.png", WINDOW_WIDTH - 22 - 5, button->GetY() + button->GetHeight() + 5);
    hoverText = new Text("fonts/Roboto-Bold.ttf", 10, BLENDED, "compartilhar", 0, 0, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE);
    hoverText->SetPos(button->GetX() - hoverText->GetWidth() - 2, button->GetY());
    botoes.push_back(make_pair(button, hoverText));

    button = new Sprite("img/Botoes/buscarme.png", WINDOW_WIDTH - 22 - 5, WINDOW_HEIGHT - 3*button->GetHeight() - 3*5);
    hoverText = new Text("fonts/Roboto-Bold.ttf", 10, BLENDED, "ampliar", 0, 0, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE);
    hoverText->SetPos(button->GetX() - hoverText->GetWidth() - 2, button->GetY());
    botoes.push_back(make_pair(button, hoverText));

    button = new Sprite("img/Botoes/ampliar.png", WINDOW_WIDTH - 22 - 5, button->GetY() + button->GetHeight() + 5);
    hoverText = new Text("fonts/Roboto-Bold.ttf", 10, BLENDED, "reduzir", 0, 0, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE);
    hoverText->SetPos(button->GetX() - hoverText->GetWidth() - 2, button->GetY());
    botoes.push_back(make_pair(button, hoverText));

    button = new Sprite("img/Botoes/reduzir.png", WINDOW_WIDTH - 22 - 5, button->GetY() + button->GetHeight() + 5);
    hoverText = new Text("fonts/Roboto-Bold.ttf", 10, BLENDED, "reduzir", 0, 0, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE);
    hoverText->SetPos(button->GetX() - hoverText->GetWidth() - 2, button->GetY());
    botoes.push_back(make_pair(button, hoverText));
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

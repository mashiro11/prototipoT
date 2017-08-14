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
    busca("img/Botoes/Topogramas_Botao_Pesquisa_1.png"),
    compartilhar("img/Botoes/Topogramas_Botao_Relacoes_1.png"),
    calendario("img/Botoes/Topogramas_Botao_Calendario_1.png"),

    zoomOut("img/Botoes/Topogramas_Botao_Afastar_1.png"),//, busca.GetX(), WINDOW_HEIGHT - 74),
    zoomIn("img/Botoes/Topogramas_Botao_Aproximar_1.png"),//, busca.GetX(), zoomOut.GetY() - zoomOut.GetHeight()),
    meEncontrar("img/Botoes/Topogramas_Botao_Localizacao_1.png"),//, busca.GetX(), zoomIn.GetY()-zoomIn.GetHeight()),

    buscaH("fonts/Roboto-Bold.ttf", 10, BLENDED, "Buscar", 0, 0, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    compartilharH("fonts/Roboto-Bold.ttf", 10, BLENDED, "Compartilhar", 0, 0, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    calendarioH("fonts/Roboto-Bold.ttf", 10, BLENDED, "Selecionar data", 0, 0, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    meEncontrarH("fonts/Roboto-Bold.ttf", 10, BLENDED, "Localizar-me", 0, 0, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    zoomInH("fonts/Roboto-Bold.ttf", 10, BLENDED, "Aproximar mapa", 0, 0, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    zoomOutH("fonts/Roboto-Bold.ttf", 10, BLENDED, "Distanciar mapa", 0, 0, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),

    showBusca(false),
    showCompartilhar(false),
    showCalendario(false),
    showMeEncontrar(false),
    showZoomIn(false),
    showZoomOut(false),

    mousePosition("fonts/Roboto-Bold.ttf", 10, BLENDED, "x", 0, 0, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    cameraFocus("fonts/Roboto-Bold.ttf", 10, BLENDED, "x", 0, 15, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    showInfo(false)
    //dBox(radius + 20 + 10 + 10,- radius - 20 - 10, fontFile, fontSize, style);
{
    bg.Resize(WINDOW_WIDTH*3, WINDOW_HEIGHT*3);
    bg.SetPosition(-WINDOW_WIDTH, -WINDOW_HEIGHT);

    busca.Resize(30, 30);
    compartilhar.Resize(30, 30);
    calendario.Resize(30, 30);

    meEncontrar.Resize(30, 30);
    zoomIn.Resize(30, 30);
    zoomOut.Resize(30, zoomOut.GetHeight());//arrumar esse sprite

    busca.SetPosition(WINDOW_WIDTH - (30 + 5), 5);
    compartilhar.SetPosition(WINDOW_WIDTH - (30 + 5), 30 + 5);
    calendario.SetPosition(WINDOW_WIDTH - (30 + 5), 30*2 + 5);

    zoomOut.SetPosition(WINDOW_WIDTH - (30 + 5), WINDOW_HEIGHT - (30 + 5) );
    zoomIn.SetPosition(WINDOW_WIDTH - (30 + 5), WINDOW_HEIGHT - (30*2 + 5));
    meEncontrar.SetPosition(WINDOW_WIDTH - (30 + 5), WINDOW_HEIGHT - (30*3 + 5));

    buscaH.SetPos(busca.GetX() - buscaH.GetWidth(), busca.GetY());
    compartilharH.SetPos(compartilhar.GetX() - compartilharH.GetWidth(), compartilhar.GetY());
    calendarioH.SetPos(calendario.GetX() - calendarioH.GetWidth(), calendario.GetY());
    meEncontrarH.SetPos(meEncontrar.GetX() - meEncontrarH.GetWidth(), meEncontrar.GetY());
    zoomInH.SetPos(zoomIn.GetX() - zoomInH.GetWidth(), zoomIn.GetY());
    zoomOutH.SetPos(zoomOut.GetX() - zoomOutH.GetWidth(), zoomOut.GetY());

    DEBUG_PRINT("zoomOut.getY()" << zoomOut.GetY());
    DEBUG_PRINT("zoomIn.getY()" << zoomIn.GetY());
    DEBUG_PRINT("meEncontrar.getY()" << meEncontrar.GetY());

    //Primeiro
    Aglutinado *ag1 = new Aglutinado(WINDOW_WIDTH/4, WINDOW_HEIGHT/4, RAIO, "fonts/Roboto-Bold.ttf", 20, BLENDED);
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
    aglutinados.push_back(new Aglutinado(WINDOW_WIDTH* 3/4.0, WINDOW_HEIGHT* 3/4.0, RAIO, "fonts/Roboto-Bold.ttf", 20, BLENDED));
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
    aglutinados.push_back(new Aglutinado(WINDOW_WIDTH* 1/4.0, WINDOW_HEIGHT* 3/4.0, RAIO, "fonts/Roboto-Bold.ttf", 20, BLENDED));
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

    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        (*it)->Update(dt);
    }

    if(!Aglutinado::selected){
        Aglutinado::aglSelected = nullptr;
        Setor::hasClick = nullptr;
    }

    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        (*it)->LateUpdate();
    }
    DialogBox::GetInstance().Update(dt);
    DialogBox::GetInstance().LateUpdate();

    OnHover();


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

void Mapa::OnHover(){
    if(InputHandler::mouseMoved){
        if(busca.IsMouseInside()) showBusca = true;
        else showBusca = false;

        if(compartilhar.IsMouseInside()) showCompartilhar = true;
        else showCompartilhar = false;

        if(calendario.IsMouseInside()) showCalendario = true;
        else showCalendario = false;

        if(meEncontrar.IsMouseInside()) showMeEncontrar = true;
        else showMeEncontrar = false;

        if(zoomIn.IsMouseInside()) showZoomIn = true;
        else showZoomIn = false;

        if(zoomOut.IsMouseInside())showZoomOut = true;
        else showZoomOut = false;
    }
}

void Mapa::Render(){
    bg.Render();
    for(auto it = aglutinados.begin(); it != aglutinados.end(); it++){
        (*it)->Render();
    }
    DialogBox::GetInstance().Render();
    busca.Render();
    compartilhar.Render();
    calendario.Render();
    meEncontrar.Render();
    zoomIn.Render();
    zoomOut.Render();

    if(showBusca) buscaH.Render();
    if(showCalendario) calendarioH.Render();
    if(showCompartilhar) compartilharH.Render();
    if(showMeEncontrar) meEncontrarH.Render();
    if(showZoomIn) zoomInH.Render();
    if(showZoomOut) zoomOutH.Render();

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

#include "Aglutinado.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
#endif //DEBUG

Aglutinado* Aglutinado::aglSelected = nullptr;

Aglutinado::Aglutinado(int x, int y, int radius, string bgFile, string fontFile, int fontSize, TextStyle style):
    dBox(x + radius + 20 + 10 + 10, y - radius - 20 - 10, bgFile, fontFile, fontSize, style),
    center(x,y),
    clicked(nullptr),
    hover(nullptr),
    circle("img/Setores/circulo72.png"),
    active(false)
{
    circle.Resize(circle.GetWidth()*1.15, circle.GetWidth()*1.15);
    circle.SetPosition(center.x - circle.GetWidth()/2, center.y - circle.GetHeight()/2);

    this->radius = radius;
    colorChange = false;

    setorWidth = SETOR_WIDTH;
    setorDist = SETOR_DIST;
    totalTermos = 0;
    animate = false;
    clockwise = false;
}

Aglutinado::~Aglutinado()
{
    //dtor
}

void Aglutinado::Draw(SDL_Renderer *renderer){
    //SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
    if(colorChange){
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        colorChange = false;
    }
    for(double i = 0; i < 2*PI; i+=0.00005){
        SDL_RenderDrawLine(renderer, center.x, center.y, center.x+radius*cos(i), center.y+radius*sin(i));
    }

    //  Desenha os setores
    for(auto it = setores.begin(); it != setores.end(); it++){
        it->second->Draw(renderer);
    }
    _resetDrawColor(renderer);
}

void Aglutinado::Render(){
    //DEBUG_PRINT("Aglutinado::Render() - inicio");
    circle.Render();
    dBox.Render();

    for(auto it = setores.begin(); it != setores.end(); it++){
        it->second->Render();
    }
    //DEBUG_PRINT("Aglutinado::Render() - fim");
}

void Aglutinado::Update(){
    //DEBUG_PRINT("Aglutinado::Update() - inicio");
    //Se clicar fora dos setores e da janela fecha as janelas
    if( IsSectorClicked() ) aglSelected = this;
    if( aglSelected != nullptr){
        Active( false );
    }else{
        Active( true );
    }
    if(!IsMouseInsideSector() && !dBox.IsMouseInside() && InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
        aglSelected = nullptr;
        active = false;
        clicked = nullptr;
        dBox.keepDBox = dBox.showDBox = dBox.showPosts = false;
        dBox.RemovePost();
    }

    if(IsMouseInside() && !IsMouseInsideSector()){
        if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
            cout << "Dentro do circulo, fora dos setores" << endl;
        }
    }

    //Atualiza cada um dos setores
    for(int i = 0; i < 2; i++){
        for(auto it = setores.begin(); it != setores.end(); it++){
            (it->second)->Update();
        }
    }

    dBox.Update();
    //Hover no setor
    if(IsMouseInsideSector()){
        //Hover + click
        //se for clicado,
        if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
            aglSelected = this;
            active = true;
            //a janela deve ser mantida aberta
            dBox.termoTemp = hover->termo;
            dBox.SetTermo(hover->termo);

            dBox.termoSelected = dBox.termoTemp;
            dBox.showDBox = true;
            dBox.keepDBox = true;


            //informa qual imagem de post deve ser renderizada
            dBox.SetPost(clicked->GetPostPath(), dBox.GetWidth());

            //caso não esteja bem posicionado, ativar a animação
            double med = clicked->angS + clicked->angF/2;
            if(med < STOP_ANGLE || med > STOP_ANGLE){
                animate = true;
            }
        }
    }else{
        //Se o mouse não está dentro do setor
        if(clicked != nullptr){
            dBox.termoTemp = clicked->termo;
            dBox.SetTermo(clicked->termo);
        }
        if(!dBox.keepDBox) dBox.showDBox = false;
    }

    //realiza a animação
    if(animate){
        double med = clicked->angS + clicked->angF/2;
        if(STOP_ANGLE - 2 <= med && med <= STOP_ANGLE + 2){
            animate = false;
        }
    }
    //DEBUG_PRINT("Aglutinado::Update() - fim");
}

void Aglutinado::SetColor(int r, int g, int b, int a){
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    colorChange = true;
}

void Aglutinado::AddTermo(string termo, string file, string posts, SDL_Color color){
    totalTermos++;
    //se NÃO for o primeiro desse termo adicionado
    if( setores.find(termo) != setores.end() ){
        setores[termo]->quantTermos++;
    }else{
        setores[termo] = new Setor(*this, termo, file, posts, this->center, this->radius);
        setores[termo]->color = color;
    }
    UpdateValues();
}

void Aglutinado::AddTermo(string termo, string file, string posts, uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    SDL_Color cor = {r, g, b, a};
    AddTermo(termo, file, posts, cor);
}

void Aglutinado::AddTermo(string termo, int quant){
    if( setores.find(termo) != setores.end() ){
        setores[termo]->quantTermos += quant;
        totalTermos += quant;
        UpdateValues();
    }
}

void Aglutinado::UpdateValues(){
    double temp;
        auto it = setores.begin();
        it->second->angS = 0;
        it->second->NewAngle(totalTermos);
        temp = it->second->angF;
        it++;
        for(; it != setores.end(); it++){
            it->second->angS = temp;
            it->second->NewAngle(totalTermos);
            temp += it->second->angF;
        }
}

void Aglutinado::_changeSetorColor(SDL_Renderer *renderer, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Aglutinado::_resetDrawColor(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

bool Aglutinado::IsMouseInside(){
    if(center.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) <= radius + setorWidth + setorDist){
            return true;
    }else return false;
}

bool Aglutinado::IsSectorClicked(){
    return( IsMouseInsideSector() && InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED );
}

bool Aglutinado::IsMouseInsideSector(){
    if(center.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) <= radius + setorWidth + setorDist &&
       center.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) >= radius + setorDist){
            return true;
    }else return false;
}

void Aglutinado::SetAlpha(int alpha){
    for(auto it = setores.begin(); it != setores.end(); it++){
        it->second->SetAlpha(alpha);
    }
    circle.SetAlpha(alpha);
}

void Aglutinado::Active(bool active){
    for(auto it = setores.begin(); it != setores.end(); it++){
        it->second->Active(active);
    }
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

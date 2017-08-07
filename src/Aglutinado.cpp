#include "Aglutinado.h"
#include "Window.h"

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
    center(x,y),
    centerRelative(x + Camera::position.x, y + Camera::position.y),
    circle("img/Setores/circulo72.png"),
    circleCenter("img/Setores/circuloCentro.png"),
    selected(false)
{
    dBox = new DialogBox(*this, radius + 20 + 10 + 10,- radius - 20 - 10, bgFile, fontFile, fontSize, style);

    circle.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
    circle.Resize(circle.GetWidth()*1.15, circle.GetWidth()*1.15);
    circle.SetPosition(centerRelative.x - circle.GetWidth()/2,
                       centerRelative.y - circle.GetHeight()/2);

    circleCenter.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
    circleCenter.Resize(radius*2, radius*2);
    circleCenter.SetPosition(centerRelative.x - circleCenter.GetWidth()/2,
                             centerRelative.y - circleCenter.GetHeight()/2);

    this->radius = radius;

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

void Aglutinado::Render(){
    //DEBUG_PRINT("Aglutinado::Render() - inicio");
    circle.Render();
    dBox->Render();

    for(auto it = setores.begin(); it != setores.end(); it++){
        it->second->Render();
    }
    if(selected){
        circleCenter.Render();
        if(!relacoes.empty()){
            for(auto it = relacoes.begin(); it != relacoes.end(); it++){
                SDL_SetRenderDrawColor(Window::GetRenderer(), 255, 255, 255, 255);
                SDL_RenderDrawLine(Window::GetRenderer(),
                                   centerRelative.x + (radius+setorDist+setorWidth)*cos(center.AngleTo((*it)->GetCenter())),
                                   centerRelative.y + (radius+setorDist+setorWidth)*sin(center.AngleTo((*it)->GetCenter())),
                                   (*it)->GetCenter().x + (radius+setorDist+setorWidth)*cos((*it)->GetCenter().AngleTo(centerRelative)),
                                   (*it)->GetCenter().y + (radius+setorDist+setorWidth)*sin((*it)->GetCenter().AngleTo(centerRelative)));
            }
        }
    }
    //DEBUG_PRINT("Aglutinado::Render() - fim");
}

void Aglutinado::Update(float dt){
    //DEBUG_PRINT("Aglutinado::Update() - inicio");
    centerRelative.x = center.x + Camera::position.x;
    centerRelative.y = center.y + Camera::position.y;

    circle.SetX(centerRelative.x - circle.GetWidth()/2);
    circle.SetY(centerRelative.y - circle.GetHeight()/2);

    //Atualiza cada um dos setores
    for(int i = 0; i < 2; i++){
        for(auto it = setores.begin(); it != setores.end(); it++){
            (it->second)->Update(dt);
        }
    }

    //Responde ao click
    if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
        if( IsMouseInside() ){
            //Indica para a classe qual é o aglomerado clicado.
            //Quando clicado, informa que o foi.
            //selected é utilizado para verificar se nenhum aglutinado foi clicado,
            //uma vez que eles só podem informar SE FORAM clicados
            aglSelected = this;
            selected = true;
        }else if(!IsMouseInside() && //Se clicou fora da dialogBox ou do aglomerado, esse aglomerado deixa de ser o selecionado
                 !dBox->IsMouseInside()){
            selected = false;
            dBox->showDBox = dBox->showPosts = false;
            dBox->RemovePost();
        }

        if(IsMouseInsideSector()){//se setor for clicado,
                //a janela deve ser mantida aberta
                dBox->termoSelected = dBox->termoTemp;
                dBox->showDBox = true;

                dBox->termoTemp = Setor::hasClick->termo;
                dBox->SetTermo(Setor::hasClick->termo);

                //informa qual imagem de post deve ser renderizada
                dBox->SetPost(Setor::hasClick->GetPostPath());

                //caso não esteja bem posicionado, ativar a animação
                double med = Setor::hasClick->angS + Setor::hasClick->angF/2;
                if(med < STOP_ANGLE || med > STOP_ANGLE){
                    animate = true;
                }
        }else if(IsMouseInsideRadius()){
            if(!relacoes.empty()){

            }
        }
    }

    dBox->Update(dt);

    if(IsMouseInside() && !IsMouseInsideSector()){
        if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
            cout << "Dentro do circulo, fora dos setores" << endl;
        }
    }

    //realiza a animação
    if(animate){
        double med = Setor::hasClick->angS + Setor::hasClick->angF/2;
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
        setores[termo] = new Setor(*this, termo, file, posts);
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
    if(centerRelative.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) <= radius + setorWidth + setorDist){
            return true;
    }else return false;
}

bool Aglutinado::IsMouseInsideRadius(){
    if(centerRelative.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) <= radius + setorWidth){
            return true;
    }else return false;
}

bool Aglutinado::IsSectorClicked(){
    return( IsMouseInsideSector() && InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED );
}

bool Aglutinado::IsAglClicked(){
    return (IsMouseInside() && !IsMouseInsideSector() && InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED);
}

bool Aglutinado::IsClicked(){
    return (IsMouseInside() && InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED);
}

bool Aglutinado::IsMouseInsideSector(){
    if(centerRelative.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) <= radius + setorWidth + setorDist &&
       centerRelative.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) >= radius + setorDist){
            return true;
    }else return false;
}

void Aglutinado::SetAlpha(int alpha){
    for(auto it = setores.begin(); it != setores.end(); it++){
        it->second->SetAlpha(alpha);
    }
    circle.SetAlpha(alpha);
}

Point& Aglutinado::GetCenter(){
    return centerRelative;
}

int& Aglutinado::GetRadius(){
    return radius;
}
bool Aglutinado::IsRelatedTo(Aglutinado* agl){
    return (relacoes.find(agl) != relacoes.end());
}

void Aglutinado::Relaciona(Aglutinado* agl){
    if(relacoes.find(agl) == relacoes.end()){
        relacoes.emplace(agl);
    }
    if(!agl->IsRelatedTo(this)){
        agl->Relaciona(this);
    }
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

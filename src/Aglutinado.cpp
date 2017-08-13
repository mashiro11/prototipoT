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
bool Aglutinado::selected(false);

Aglutinado::Aglutinado(int x, int y, int radius, string bgFile, string fontFile, int fontSize, TextStyle style):
    center(x,y),
    centerRelative(x + Camera::position.x, y + Camera::position.y),
    circle("img/Setores/circulo.png"),
    circleCenter("img/Setores/circuloCentro.png"),
    showRelations(false),
    showCircleCenter(false),
    showLine(false),
    hasSectorSelected(false),
    enquadramento(ENQUADRAMENTO_X + center.x, ENQUADRAMENTO_Y + center.y)
{
    dBox = new DialogBox(*this, radius + 20 + 10 + 10,- radius - 20 - 10, bgFile, fontFile, fontSize, style);

    setorWidth = SETOR_WIDTH;
    setorDist = SETOR_DIST;

    circle.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
    circle.Resize(radius*2 + setorDist*2 + setorWidth*2 + 20,
                  radius*2 + setorDist*2 + setorWidth*2 + 20);
    circle.SetPosition(centerRelative.x - circle.GetWidth()/2,
                       centerRelative.y - circle.GetHeight()/2);

    circleCenter.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
    circleCenter.Resize(radius*2, radius*2);
    circleCenter.SetPosition(centerRelative.x - circleCenter.GetWidth()/2,
                             centerRelative.y - circleCenter.GetHeight()/2);

    this->radius = radius;

    totalTermos = 0;
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
    if(showCircleCenter){
        circleCenter.Render();
    }
    if(showRelations){
        if(!relacoes.empty()){
            for(auto it = relacoes.begin(); it != relacoes.end(); it++){
                SDL_SetRenderDrawColor(Window::GetRenderer(), 255, 255, 255, 255);
                float cosThisOther = cos(centerRelative.AngleTo((*it)->GetCenter()));
                float sinThisOther = sin(centerRelative.AngleTo((*it)->GetCenter()));

                float cosOtherThis = cos((*it)->GetCenter().AngleTo(centerRelative));
                float sinOtherThis = sin((*it)->GetCenter().AngleTo(centerRelative));
                SDL_RenderDrawLine(Window::GetRenderer(),
                                   centerRelative.x + (circle.GetWidth()/2)*cosThisOther,
                                   centerRelative.y + (circle.GetWidth()/2)*sinThisOther,
                                   (*it)->GetCenter().x + ((*it)->GetRadiusExternal()/2)*cosOtherThis,
                                   (*it)->GetCenter().y + ((*it)->GetRadiusExternal()/2)*sinOtherThis);
            }
        }
    }
    //DEBUG
    if(showLine){
        ShowDebugLines();
    }
    //DEBUG_PRINT("Aglutinado::Render() - fim");
}

void Aglutinado::Update(float dt){
    //DEBUG_PRINT("Aglutinado::Update() - inicio");

    UpdatePositions(dt);
    UpdateSectors(dt);
    OnClick();
    OnHover();

    dBox->Update(dt);

    //DEBUG
    if(InputHandler::GetKey() == SDLK_0){
        showLine = !showLine;
    }
    //DEBUG_PRINT("Aglutinado::Update() - fim");
}

void Aglutinado::LateUpdate(){
    for(auto it = setores.begin(); it != setores.end(); it++){
        (it->second)->LateUpdate();
    }
}

void Aglutinado::UpdatePositions(float dt){
    if(Camera::cameraMove){
        centerRelative.x = center.x - Camera::position.x;
        centerRelative.y = center.y - Camera::position.y;

        circle.SetX(centerRelative.x - circle.GetWidth()/2);
        circle.SetY(centerRelative.y - circle.GetHeight()/2);

        circleCenter.SetX(centerRelative.x - circleCenter.GetWidth()/2);
        circleCenter.SetY(centerRelative.y - circleCenter.GetHeight()/2);

        enquadramento.x = ENQUADRAMENTO_X + center.x;
        enquadramento.y = ENQUADRAMENTO_Y + center.y;
    }
}

void Aglutinado::UpdateSectors(float dt){
    //Atualiza primeiro o setor que foi clicado
    if(Setor::hasClick != nullptr){
        for(auto it = setores.begin(); it != setores.end(); it++){
            if(it->second == Setor::hasClick) it->second->Update(dt);
        }
    }
    //Atualiza todos, exceto o que foi clicado
    for(auto it = setores.begin(); it != setores.end(); it++){
        if(it->second == Setor::hasClick) continue;
        (it->second)->Update(dt);
    }
}

void Aglutinado::OnClick(){
    //DEBUG_PRINT("Aglutinado::OnClick() - inicio");
    //Reação a click
    if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
        if(circleCenter.IsMouseInside()){
            SelectAglutinado();
            showRelations = true;
            circleCenter.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
        }
        if(IsMouseInsideSector()){
            hasSectorSelected = true;
        }

        if(IsOutside() && (aglSelected == this) && !dBox->transfer){//Se clicou fora do aglomerado
            showRelations = false;
            showCircleCenter = false;
            UnselectAglutinado();
        }
    }
    //DEBUG_PRINT("Aglutinado::OnClick() - fim");
}

void Aglutinado::OnHover(){
    //DEBUG_PRINT("Aglutinado::OnHover() - inicio");
    if(InputHandler::mouseMoved){
        if(IsMouseInsideExternalRadius()){
            showCircleCenter = true;
        }else{
            if(showRelations){
                circleCenter.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
            }else{
                showCircleCenter = false;
            }
        }
        if(IsMouseInsideInternalRadius()){
            if(!showRelations){
                circleCenter.SetAlpha(SDL_ALPHA_OPAQUE);
            }else{
                circleCenter.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
            }
        }else{
            circleCenter.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
        }
    }
    //DEBUG_PRINT("Aglutinado::OnHover() - fim");
}

DialogBox* Aglutinado::GetDialogBox(){
    return dBox;
}

void Aglutinado::SelectAglutinado(){
    aglSelected = this;
    selected = true;
    circle.SetAlpha(SDL_ALPHA_OPAQUE);
}

void Aglutinado::UnselectAglutinado(){
    showRelations = false;
    selected = false;
    circle.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
}

void Aglutinado::AddTermo(string termo, string file, string posts){
    totalTermos++;
    //se NÃO for o primeiro desse termo adicionado
    if( setores.find(termo) != setores.end() ){
        setores[termo]->quantTermos++;
    }else{
        setores[termo] = new Setor(*this, termo, file, posts);
    }
    UpdateValues();
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

bool Aglutinado::IsOutside(){
    bool cumulativeCondition = false;
    cumulativeCondition |= circle.IsMouseInside();
    cumulativeCondition |= (dBox->showDBox ? dBox->IsMouseInside(): false) ;
    return !cumulativeCondition;
}

bool Aglutinado::IsMouseInsideInternalRadius(){
    if(centerRelative.DistTo(InputHandler::GetMousePosition().x, InputHandler::GetMousePosition().y ) <= circleCenter.GetWidth()/2){
            return true;
    }else return false;
}

bool Aglutinado::IsMouseInsideExternalRadius(){
    if(centerRelative.DistTo(InputHandler::GetMousePosition().x, InputHandler::GetMousePosition().y ) <= circle.GetWidth()/2){
            return true;
    }else return false;
}

bool Aglutinado::IsMouseInsideSector(){
    if(centerRelative.DistTo(InputHandler::GetMousePosition().x, InputHandler::GetMousePosition().y ) <= radius + setorWidth + setorDist &&
       centerRelative.DistTo(InputHandler::GetMousePosition().x, InputHandler::GetMousePosition().y ) >= radius + setorDist){
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

Point& Aglutinado::GetFixedCenter(){
    return center;
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

void Aglutinado::Shrink(float percent){
    radius *= percent;
    setorDist *= percent;
    setorWidth *= percent;

    circle.Resize(circle.GetWidth()*percent, circle.GetHeight()*percent);
    circle.SetPosition(center.x - circle.GetWidth()/2, center.y - circle.GetHeight()/2);
    DEBUG_PRINT(circle.GetX() << "x" << circle.GetY());

    circleCenter.Resize(circleCenter.GetWidth()*percent, circleCenter.GetHeight()*percent);
    circleCenter.SetPosition(center.x - circleCenter.GetWidth()/2, center.y - circleCenter.GetHeight()/2);

    for(auto it = setores.begin(); it != setores.end(); it++){
        it->second->Shrink(percent);
    }
}

int Aglutinado::GetRadiusExternal(){
    return circle.GetWidth();
}

void Aglutinado::ShowDebugLines(){
    SDL_SetRenderDrawColor(Window::GetRenderer(), 255, 0, 0, 255);
    SDL_RenderDrawPoint(Window::GetRenderer(), centerRelative.x, centerRelative.y);
    if(IsMouseInsideInternalRadius()){
            SDL_SetRenderDrawColor(Window::GetRenderer(), 255, 0, 0, 255);
        }else if(IsMouseInsideExternalRadius()){
            SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 255, 0, 255);
    }

    if(IsMouseInsideExternalRadius()){
        SDL_RenderDrawLine(Window::GetRenderer(), centerRelative.x, centerRelative.y,
                           InputHandler::GetMousePosition().x, InputHandler::GetMousePosition().y);
    }
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

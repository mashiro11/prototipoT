#include "Aglutinado.h"

Aglutinado::Aglutinado(int x, int y, int radius)
{
    center.x = x;
    center.y = y;
    this->radius = radius;
    colorChange = false;

    setorWidth = SETOR_WIDTH;
    setorDist = SETOR_DIST;
    totalTermos = 0;
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
    for(auto it = setores.begin(); it != setores.end(); it++){
        it->second->Render();
    }
}

void Aglutinado::Update(){
    if(IsMouseInside() && !IsMouseInsideSector()){
        if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
                    cout << "Dentro do circulo, fora dos setores" << endl;
        }
    }
    for(auto it = setores.begin(); it != setores.end(); it++){
        (it->second)->Update();
    }
}

void Aglutinado::SetColor(int r, int g, int b, int a){
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    colorChange = true;
}

void Aglutinado::AddTermo(string termo, string file, SDL_Color color){
    totalTermos++;
    //se NÃO for o primeiro desse termo adicionado
    if( setores.find(termo) != setores.end() ){
        setores[termo]->quantTermos++;
    }else{
        setores[termo] = new Setor(termo, file, this->center, this->radius);
        setores[termo]->color = color;
    }
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

    for(auto it = setores.begin(); it != setores.end(); it++){
        cout << it->second->termo << " - angS: " << it->second->angS << "  angF: " << it->second->angF << endl;
    }
    cout << endl;
}

void Aglutinado::AddTermo(string termo, string file, uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    SDL_Color cor = {r, g, b, a};
    AddTermo(termo, file, cor);
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

bool Aglutinado::IsMouseInsideSector(){
    if(center.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) <= radius + setorWidth + setorDist &&
       center.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) >= radius + setorDist){
            return true;
    }else return false;
}

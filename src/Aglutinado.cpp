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
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_MOD);
    if(colorChange){
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        colorChange = false;
    }
    for(double i = 0; i < 2*PI; i+=0.00005){
        SDL_RenderDrawLine(renderer, center.x, center.y, center.x+radius*cos(i), center.y+radius*sin(i));
    }

    //  Desenha os setores
    double j = 0;
    Setor* setor;
    for(auto it = setores.begin(); it != setores.end(); it++){
        setor = it->second;
        _changeSetorColor(renderer, setor->color );
        setor->angS = j;

        for (double k = 0; k < 2*PI* setor->quantTermos/totalTermos; j+=0.0001, k += 0.0001){
            SDL_RenderDrawLine(renderer, center.x+(radius+setorDist)*cos(j), center.y+(radius+setorDist)*sin(j),
                               center.x+(radius+setorDist+setorWidth)*cos(j), center.y+(radius+setorDist+setorWidth)*sin(j));
        }
        setor->angF = j;
    }
    _resetDrawColor(renderer);
}

void Aglutinado::Render(){

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

void Aglutinado::AddTermo(string termo, SDL_Color color){
    //se NÃO for o primeiro desse termo adicionado
    if( setores.find(termo) != setores.end() ){
        setores[termo]->quantTermos++;
    }else{
        setores[termo] = new Setor(termo, this->center, this->radius);
        setores[termo]->color = color;
    }
    totalTermos++;
}

void Aglutinado::AddTermo(string termo, uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    SDL_Color cor = {r, g, b, a};
    AddTermo(termo, cor);
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

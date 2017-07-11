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
    //SDL_Rect rect = {100, 150, 800, 300};
    //SDL_SetRenderDrawColor(renderer, 0,100,200,255);
    //SDL_RenderFillRect(renderer, &rect);
    //SDL_RenderDrawRect(renderer, &rect);
    if(colorChange){
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        colorChange = false;
    }
    //SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
    //SDL_SetRenderDrawColor(renderer, 255,0,0,10);
    //  Desenha o circulo
    for(double i = 0; i < 2*PI; i+=0.00005){
        SDL_RenderDrawLine(renderer, center.x, center.y, center.x+radius*cos(i), center.y+radius*sin(i));
    }

    //  Desenha os setores

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    double j = 0;
    for(auto it = termos.begin(); it != termos.end(); it++){
        _changeSetorColor(renderer, (it->second).second );
        angles[(it->first)].first = j;

        for (double k = 0; k < 2*PI* ((it->second).first)/totalTermos; j+=0.0001, k += 0.0001){
            SDL_RenderDrawLine(renderer, center.x+(radius+setorDist)*cos(j), center.y+(radius+setorDist)*sin(j),
                               center.x+(radius+setorDist+setorWidth)*cos(j), center.y+(radius+setorDist+setorWidth)*sin(j));
        }
        angles[(it->first)].second = j;
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
    for(auto it = angles.begin(); it != angles.end(); it++){
        if(IsMouseInsideSector(it->first)){
                if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
                    cout << it->first << endl;
                }
        }
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
    if(termos.find(termo) != termos.end()){
        termos[termo].first++;
    }else{
        termos[termo].first = 1;
        termos[termo].second = color;

        angles[termo].second = 0;
        //janelasTermo[termo].second = new Sprite();
    }
    totalTermos++;
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

bool Aglutinado::IsMouseInsideSector(string termo){
    if(center.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) <= radius + setorWidth + setorDist &&
       center.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) >= radius + setorDist  &&
       center.AngleTo(InputHandler::GetMouseX(), InputHandler::GetMouseY()) >= angles[termo].first &&
       center.AngleTo(InputHandler::GetMouseX(), InputHandler::GetMouseY()) <= angles[termo].second) {
            return true;
    }else return false;
}

#include "Setor.h"

//Setor::Setor():center(0,0), percent(0), radius(0)
//{
//    //ctor
//}

Setor::Setor(string termo, string file, Point center, double radius):
    percent(0),
    sp(file)
{
    SDL_Point pt;
    pt.x = center.x;
    pt.y = center.y;
    sp.SetRotationPoint(pt);
    sp.SetX(center.x);
    sp.SetY(center.y - radius);
    this->termo = termo;
    this->quantTermos = 1;
    this->center = center;
    this->radius = radius;
    this->angS = 0;
    setorWidth = SETOR_WIDTH;
    setorDist = SETOR_DIST;
}

Setor::~Setor()
{
    //dtor
}

void Setor::Render(){
    for (double k = angS; k < angF + angS; k += 0.01){
        sp.SetRotationAngle(k);
        sp.Render();
    }
}

void Setor::Draw(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (double k = angS; k < angF + angS; k += 0.01){
            SDL_RenderDrawLine(renderer, center.x+(radius+setorDist)*cos(k), center.y+(radius+setorDist)*sin(k),
                               center.x+(radius+setorDist+setorWidth)*cos(k), center.y+(radius+setorDist+setorWidth)*sin(k));
    }
}

void Setor::Update(){
    angS += 0.01;
    if(IsMouseInside()){
        if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
            cout << termo << endl;
        }
    }
}

void Setor::SetColor(SDL_Color color){
    this->color.r = color.r;
    this->color.g = color.g;
    this->color.b = color.b;
    this->color.a = color.a;
}

void Setor::SetColor(int r, int g, int b, int a){
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
    this->color.a = a;
}

void Setor::SetPercent(double percent){
    this->percent = percent;
}

void Setor::SetAng(double ang){
    this->angS = ang;
    this->angF = 2*PI*percent + angS;
}

bool Setor::IsMouseInside(){
    if(center.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) <= radius + setorWidth + setorDist &&
       center.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) >= radius + setorDist  &&
       center.AngleTo(InputHandler::GetMouseX(), InputHandler::GetMouseY()) >= angS &&
       center.AngleTo(InputHandler::GetMouseX(), InputHandler::GetMouseY()) <= angF + angS) {
            return true;
    }else return false;
}

void Setor::NewAngle(int totalTermos){
    angF = 2*PI* quantTermos/totalTermos;
}

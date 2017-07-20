#include "Setor.h"

Setor::Setor():center(0,0), percent(0), radius(0)
{
    //ctor
}

Setor::Setor(string termo, Point center, double radius):percent(0)
{
    this->termo = termo;
    this->quantTermos = 1;
    this->center = center;
    this->radius = radius;
    setorWidth = SETOR_WIDTH;
    setorDist = SETOR_DIST;

}

Setor::~Setor()
{
    //dtor
}

void Setor::Render(){
}

void Setor::Update(){
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
       center.AngleTo(InputHandler::GetMouseX(), InputHandler::GetMouseY()) <= angF) {
            return true;
    }else return false;
}

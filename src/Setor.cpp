#include "Setor.h"

Setor::Setor():center(0,0), percent(0), radius1(0), radius2(0)
{
    //ctor
}

Setor::Setor(Point center, double radius1, double radius2):percent(0)
{
    this->center = center;
    this->radius1 = radius1;
    this->radius2 = radius2;
}

Setor::~Setor()
{
    //dtor
}

void Setor::Render(){
}

void Setor::Update(){
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

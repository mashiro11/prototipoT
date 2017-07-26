#include "Setor.h"

//Setor::Setor():center(0,0), percent(0), radius(0)
//{
//    //ctor
//}

Setor** Setor::scopy = nullptr;
bool* Setor::animate = nullptr;
bool* Setor::clockwise = nullptr;

Setor::Setor(string termo, string file, string posts, Point center, double radius):
    percent(0),
    sp(file),
    posts(posts)
{
    this->termo = termo;
    this->quantTermos = 1;
    this->center = center;
    this->radius = radius;
    this->angS = 0;
    setorDist = SETOR_DIST;
    setorWidth = SETOR_WIDTH;

    SDL_Point pt;
    pt.x = - radius - setorDist;
    pt.y = 0;
    sp.SetRotationPoint(pt);
    sp.SetX(center.x + radius + setorDist);
    sp.SetY(center.y);
    sp.Transform(-1, 11);

    showPosts = false;
}

Setor::~Setor()
{
    //dtor
}

void Setor::Render(){
    for (double k = angS; k + sp.GetHeight() < angF + angS; k += 6){
        sp.SetRotationAngle(k);
        sp.Render();
    }
}

void Setor::Draw(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (double k = angS; k < angF + angS; k += 0.001){
            SDL_RenderDrawLine(renderer, center.x+(radius+setorDist)*cos(k), center.y+(radius+setorDist)*sin(k),
                               center.x+(radius+setorDist+setorWidth)*cos(k), center.y+(radius+setorDist+setorWidth)*sin(k));
    }
}

void Setor::Update(){
    if(*animate){
        angS += ANIMATION_SPEED;
        if(angS >= 360) angS -= 360;
    }
    if(IsMouseInside()){//InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED && IsMouseInside()){
        //se n�o estiver rolando anima��o, pode colocar a si mesmo no scopy
        if( !(*animate) )*scopy = this;
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
    this->angF = 360*percent + angS;
}

bool Setor::IsMouseInside(){
    double dist = center.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY());
    //angulo em graus
    double angle = (180/PI) * center.AngleTo(InputHandler::GetMouseX(), InputHandler::GetMouseY());
    if(dist <= radius + setorWidth + setorDist &&
       dist >= radius + setorDist){
           if(( angS <= angle && angle <= angS + angF) ||
              ( angS <= (angle + 360) && (angle + 360) <= angS + angF)){
                   return true;
            } else return false;
    }else return false;
}

void Setor::NewAngle(int totalTermos){
    angF = 360* quantTermos/totalTermos;
}

void Setor::SetCopyAddress(Setor** setor){
    scopy = setor;
}

void Setor::SetAnimateAddress(bool* address){
    animate = address;
}

void Setor::SetAnimationOrientation(bool* clockwise){
    Setor::clockwise = clockwise;
}

string Setor::GetPostPath(){
    return posts;
}
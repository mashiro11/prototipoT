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
    this->posts.SetX(center.x + radius + setorDist + sp.GetWidth() + 40);
    this->posts.SetY(center.y - radius - setorDist - sp.GetWidth() + 40);
    this->posts.Transform(104 + this->posts.GetWidth(), -1);
    this->posts.Clip(this->posts.GetWidth(), 185 - 40); //185 da box e 40 para compensar oq desceu
}

Setor::~Setor()
{
    //dtor
}

void Setor::Render(){
    for (double k = angS; k + sp.GetHeight() < angF + angS; k += 0.1){
        sp.SetRotationAngle(k);
        sp.Render();
    }
    if(showPosts){
        posts.Render();
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
//        if(*clockwise) angS += 1;
//        else angS -= 1;

        if(angS >= 360) angS -= 360;
//        else if(angS <= 0) angS += 360;
    }
    if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED && IsMouseInside()){
        *scopy = this;
        showPosts = true;
    }
    if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED && !IsMouseInside()){
        showPosts = false;
    }
    if(showPosts && posts.IsMouseInside()){
        posts.SlideClip(0, InputHandler::GetMouseScrollY()*SCROLL_SPEED);
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
    if(center.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) <= radius + setorWidth + setorDist &&
       center.DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY() ) >= radius + setorDist  &&
       center.AngleTo(InputHandler::GetMouseX(), InputHandler::GetMouseY())*180/PI >= angS &&
       center.AngleTo(InputHandler::GetMouseX(), InputHandler::GetMouseY())*180/PI <= angF + angS) {
            return true;
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

#include "Setor.h"

//#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
#endif //DEBUG

Setor* Setor::hasClick = nullptr;

Setor::Setor(Aglutinado &agl, string termo, string file, string posts, Point center, double radius):
    agl(agl),
    termBox("img/termbox.png", center.x, center.y),
    termSetor("fonts/Roboto-Bold.ttf", 10, BLENDED, termo, center.x, center.y, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    showTermbox(false),
    percent(0),
    sp(file),
    posts(posts),
    hadMouseHover(false),
    baseAlpha(SDL_ALPHA_OPAQUE*0.5)
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

    sp.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
}

Setor::~Setor()
{
    //dtor
}

void Setor::Render(){

    for (double k = angS; k + sp.GetHeight() < angF + angS; k += 10){
        sp.SetRotationAngle(k);
        sp.Render();
    }

    if(showTermbox){
        termBox.Render();
        termSetor.Render();

        double mediana = angS+angF/2;
        if (0 <= mediana && mediana <= 90){
            SDL_RenderDrawLine(Window::GetRenderer(),
                               termBox.GetX(), termBox.GetY(),
                               center.x, center.y);
        }else if(90 < mediana && mediana <= 180 ){
            SDL_RenderDrawLine(Window::GetRenderer(),
                               termBox.GetX() + termBox.GetWidth(), termBox.GetY(),
                               center.x, center.y);
        }else if(180 < mediana && mediana < 270){
            SDL_RenderDrawLine(Window::GetRenderer(),
                               termBox.GetX() + termBox.GetWidth(), termBox.GetY() + termBox.GetHeight(),
                               center.x, center.y);
        }else if(270 <= mediana && mediana <= 360){//primeiro ou quarto quadrantes
            SDL_RenderDrawLine(Window::GetRenderer(), termBox.GetX(),
                               termBox.GetY() + termBox.GetHeight(),
                               center.x, center.y);
        }
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
    if(agl.animate){
        angS += ANIMATION_SPEED;
        if(angS >= 360) angS -= 360;
    }
    //Durante a animação as respostas ao mouse são desligadas
    PositionTermbox();
    AdjustOpacity();
    if( !(agl.animate) ){
        if(IsMouseInside()){//MouseHover
            if(hadMouseHover == false){//entrou
                //agl.hover = this;
                hadMouseHover = true;
                sp.SetAlpha(SDL_ALPHA_OPAQUE);

                if(hasClick != this){//se não for esse o setor clicado
                    showTermbox = true;
                }
            }
        }else{//se não está em MouseHover
            if(hadMouseHover == true){//se saiu do mouseHover
                hadMouseHover = false;
                showTermbox = false;
            }
        }
        if(IsClicked()){
            hasClick = this;
        }
    }
}

void Setor::PositionTermbox(){
    double mediana = angS+angF/2;
    if(0 < mediana && mediana <= 90){//primeiro quadrante
        termBox.SetPosition(center.x+(radius+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                            center.y+(radius+setorDist+sp.GetWidth())*sin( mediana *PI/180));

        termSetor.SetPos(center.x+(radius+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                         center.y+(radius+setorDist+sp.GetWidth())*sin( mediana *PI/180));

    }else if(90 < mediana && mediana <= 180){//segundo quadrante
        termBox.SetPosition(center.x - termBox.GetWidth() +(radius+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                            center.y +(radius+setorDist+sp.GetWidth())*sin( mediana *PI/180));

        termSetor.SetPos(center.x - termBox.GetWidth() +(radius+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                         center.y +(radius+setorDist+sp.GetWidth())*sin( mediana *PI/180));
    }else if(180 < mediana && mediana <= 270){
        termBox.SetPosition(center.x - termBox.GetWidth() +(radius+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                            center.y - termBox.GetHeight() +(radius+setorDist+sp.GetWidth())*sin( mediana *PI/180));

        termSetor.SetPos(center.x - termBox.GetWidth() +(radius+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                         center.y - termBox.GetHeight() +(radius+setorDist+sp.GetWidth())*sin( mediana *PI/180));

    }else if(270 < mediana && mediana <= 360){
        termBox.SetPosition(center.x +(radius+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                            center.y - termBox.GetHeight() +(radius+setorDist+sp.GetWidth())*sin( mediana *PI/180));

        termSetor.SetPos(center.x +(radius+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                         center.y - termBox.GetHeight() +(radius+setorDist+sp.GetWidth())*sin( mediana *PI/180));
    }
}

void Setor::AdjustOpacity(){
    if(hasClick == nullptr){
        sp.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
    }else if(hasClick != this){
        sp.SetAlpha(SDL_ALPHA_OPAQUE*0.2);
    }else if(hasClick == this){
        sp.SetAlpha(SDL_ALPHA_OPAQUE);
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

bool Setor::IsClicked(){
    return (IsMouseInside() && InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED);
}

bool Setor::ClickedOut(){
    return (!IsMouseInside() && InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED);
}

void Setor::NewAngle(int totalTermos){
    angF = 360* quantTermos/totalTermos;
}

string Setor::GetPostPath(){
    return posts;
}

void Setor::SetAlpha(int alpha){
    sp.SetAlpha(alpha);
}



#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

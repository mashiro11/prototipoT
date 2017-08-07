#include "Setor.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
#endif //DEBUG

Setor* Setor::hasClick = nullptr;

Setor::Setor(Aglutinado &agl, string termo, string tipo, string posts):
    agl(agl),
    termBox("img/termbox.png", agl.GetCenter().x, agl.GetCenter().y),
    termSetor("fonts/Roboto-Bold.ttf", 10, BLENDED, termo, agl.GetCenter().x, agl.GetCenter().y, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    showTermbox(false),
    percent(0),
    sp("img/Setores/"+tipo+".png"),
    posts("img/Posts/"+ tipo + "/" + posts + ".png"),
    hadMouseHover(false),
    baseAlpha(SDL_ALPHA_OPAQUE*0.5)
{
    sp.Resize(20, 5);
    this->termo = termo;
    this->quantTermos = 1;
    this->angS = 0;
    setorDist = SETOR_DIST;
    setorWidth = SETOR_WIDTH;

    SDL_Point pt;
    pt.x = - agl.GetRadius() - setorDist;
    pt.y = 0;
    sp.SetRotationPoint(pt);
    sp.SetX(agl.GetCenter().x + agl.GetRadius() + setorDist);
    sp.SetY(agl.GetCenter().y - radius);
    sp.Transform(-1, 11);

    sp.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
    timer.Set(3000);
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
        SDL_SetRenderDrawColor(Window::GetRenderer(), 0,0,0,SDL_ALPHA_OPAQUE);
        double mediana = angS+angF/2;
        if (0 <= mediana && mediana <= 90){
            SDL_RenderDrawLine(Window::GetRenderer(),
                               termBox.GetX(), termBox.GetY(),
                               agl.GetCenter().x, agl.GetCenter().y);
        }else if(90 < mediana && mediana <= 180 ){
            SDL_RenderDrawLine(Window::GetRenderer(),
                               termBox.GetX() + termBox.GetWidth(), termBox.GetY(),
                               agl.GetCenter().x, agl.GetCenter().y);
        }else if(180 < mediana && mediana < 270){
            SDL_RenderDrawLine(Window::GetRenderer(),
                               termBox.GetX() + termBox.GetWidth(), termBox.GetY() + termBox.GetHeight(),
                               agl.GetCenter().x, agl.GetCenter().y);
        }else if(270 <= mediana && mediana <= 360){//primeiro ou quarto quadrantes
            SDL_RenderDrawLine(Window::GetRenderer(), termBox.GetX(),
                               termBox.GetY() + termBox.GetHeight(),
                               agl.GetCenter().x, agl.GetCenter().y);
        }
    }
}

void Setor::Draw(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (double k = angS; k < angF + angS; k += 0.001){
            SDL_RenderDrawLine(renderer, agl.GetCenter().x+(agl.GetRadius()+setorDist)*cos(k), agl.GetCenter().y+(agl.GetRadius()+setorDist)*sin(k),
                               agl.GetCenter().x+(agl.GetRadius()+setorDist+setorWidth)*cos(k), agl.GetCenter().y+(agl.GetRadius()+setorDist+setorWidth)*sin(k));
    }
}

void Setor::Update(float dt){
    if(agl.animate){
        angS += ANIMATION_SPEED;
        if(angS >= 360) angS -= 360;
    }

    //Quando for suavisar o tempo de aparecer cada um
    if(hasClick != nullptr){
        timer.Update(dt);
    }

    sp.SetX(agl.GetCenter().x + agl.GetRadius() + setorDist);
    sp.SetY(agl.GetCenter().y);

    termSetor.SetX(termSetor.GetX() + agl.GetCenter().x);
    termSetor.SetY(termSetor.GetY() + agl.GetCenter().y);
    //Durante a animação as respostas ao mouse são desligadas
    PositionTermbox();

    AdjustOpacity();

    if( !(agl.animate) ){
        if(IsMouseInside()){//MouseHover
            if(hadMouseHover == false){//entrou
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

            timer.Restart();
        }
    }
}

void Setor::PositionTermbox(){
    double mediana = angS+angF/2;
    if(0 < mediana && mediana <= 90){//primeiro quadrante
        termBox.SetPosition(agl.GetCenter().x+(agl.GetRadius()+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                            agl.GetCenter().y+(agl.GetRadius()+setorDist+sp.GetWidth())*sin( mediana *PI/180));

        termSetor.SetPos(agl.GetCenter().x+(agl.GetRadius()+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                         agl.GetCenter().y+(agl.GetRadius()+setorDist+sp.GetWidth())*sin( mediana *PI/180));

    }else if(90 < mediana && mediana <= 180){//segundo quadrante
        termBox.SetPosition(agl.GetCenter().x - termBox.GetWidth() +(agl.GetRadius()+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                            agl.GetCenter().y +(agl.GetRadius()+setorDist+sp.GetWidth())*sin( mediana *PI/180));

        termSetor.SetPos(agl.GetCenter().x - termBox.GetWidth() +(agl.GetRadius()+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                         agl.GetCenter().y +(agl.GetRadius()+setorDist+sp.GetWidth())*sin( mediana *PI/180));

    }else if(180 < mediana && mediana <= 270){
        termBox.SetPosition(agl.GetCenter().x - termBox.GetWidth() +(agl.GetRadius()+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                            agl.GetCenter().y - termBox.GetHeight() +(agl.GetRadius()+setorDist+sp.GetWidth())*sin( mediana *PI/180));

        termSetor.SetPos(agl.GetCenter().x - termBox.GetWidth() +(agl.GetRadius()+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                         agl.GetCenter().y - termBox.GetHeight() +(agl.GetRadius()+setorDist+sp.GetWidth())*sin( mediana *PI/180));

    }else if(270 < mediana && mediana <= 360){
        termBox.SetPosition(agl.GetCenter().x +(agl.GetRadius()+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                            agl.GetCenter().y - termBox.GetHeight() +(agl.GetRadius()+setorDist+sp.GetWidth())*sin( mediana *PI/180));

        termSetor.SetPos(agl.GetCenter().x +(agl.GetRadius()+setorDist+sp.GetWidth())*cos( mediana *PI/180),
                         agl.GetCenter().y - termBox.GetHeight() +(agl.GetRadius()+setorDist+sp.GetWidth())*sin( mediana *PI/180));
    }
}

void Setor::AdjustOpacity(){
    if(hasClick == nullptr){
        sp.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
    }else if(hasClick != this){
        if(termo == hasClick->termo){// && timer.TimeUp()){
            timer.Restart();
            sp.SetAlpha(SDL_ALPHA_OPAQUE);
        }else{
            sp.SetAlpha(SDL_ALPHA_OPAQUE*0.2);
        }
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
    double dist = agl.GetCenter().DistTo(InputHandler::GetMouseX(), InputHandler::GetMouseY());
    //angulo em graus
    double angle = (180/PI) * agl.GetCenter().AngleTo(InputHandler::GetMouseX(), InputHandler::GetMouseY());
    if(dist <= agl.GetRadius() + setorWidth + setorDist &&
       dist >= agl.GetRadius() + setorDist){
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

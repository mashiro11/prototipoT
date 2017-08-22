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
set<Setor*> Setor::setoresTermo;
bool Setor::animate(false);
int Setor::setorIncrement(0);
bool Setor::showLines(false);
float Setor::diff(0);

Setor::Setor(Aglutinado &agl, string termo, string tipo):
    agl(agl),
    tipo(tipo),
    termBox("img/termbox.png", agl.GetCenter().x, agl.GetCenter().y),
    termSetor("fonts/Roboto-Bold.ttf", 10, BLENDED, termo, agl.GetCenter().x, agl.GetCenter().y, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    showTermbox(false),
    percent(0),
    sp("img/Setores/"+tipo+".png"),
    //posts("img/Posts/"+ tipo + "/" + posts + ".png"),
    hadMouseHover(false),
    baseAlpha(SDL_ALPHA_OPAQUE*0.5)
//    state(OPACITY_DEFAULT)
{
    DEBUG_PRINT("Setor: " << this);
    DEBUG_PRINT("   pertenço a: " << &agl);
    posts.push_back("img/Posts/"+ tipo + "/" + termo + "_Facebook.png");
    posts.push_back("img/Posts/"+ tipo + "/" + termo + "_Instagram.png");
    posts.push_back("img/Posts/"+ tipo + "/" + termo + "_Twitter.png");
    posts.push_back("img/Posts/"+ tipo + "/" + termo + "_Topogramas.png");
    sp.Resize(20, 5);
    this->termo = termo;
    this->quantTermos = 1;
    this->angS = 0;
    termBox.SetWidth(termSetor.GetWidth());
    if(tipo == "hashtagfeliz"){
        termSetor.SetColor(0xFA, 0xB4, 0x00, SDL_ALPHA_OPAQUE);
    }else if(tipo == "hashtagtriste"){
        termSetor.SetColor(0x05, 0x8C, 0xF1, SDL_ALPHA_OPAQUE);
    }else if(tipo == "termofeliz"){
        termSetor.SetColor(0xF9, 0xD6, 0x26, SDL_ALPHA_OPAQUE);
    }else if(tipo == "termotriste"){
        termSetor.SetColor(0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE);
    }

    SDL_Point pt;
    pt.x = - agl.GetRadius() - agl.setorDist;
    pt.y = 0;
    sp.SetRotationPoint(pt);
    sp.SetX(agl.GetCenter().x + agl.GetRadius() + agl.setorDist);
    sp.SetY(agl.GetCenter().y - agl.GetRadius());
    sp.Transform(-1, 11);

    sp.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
    timer.Set(3000);
}

Setor::~Setor()
{
    //dtor
}

void Setor::Render(){

    for (int k = angS; k + sp.GetHeight() < angF + angS; k += sp.GetHeight()){
        sp.SetRotationAngle(k);
        sp.Render();
    }

    if(showTermbox){
        termBox.Render();
        termSetor.Render();

        //DEBUG
        if(showLines){
            ShowLines();
        }
    }
}

void Setor::Update(float dt){
    //DEBUG_PRINT("Setor::Update() - inicio");
    UpdatePosition(dt);
//    AdjustOpacity();
    //Quando for montar a lista de quais os setores com mesmo termo
    if(hasClick != nullptr){
        if(!setoresTermo.empty()){
            if((*setoresTermo.begin())->termo == termo &&
                setoresTermo.find(this) == setoresTermo.end()){
                    setoresTermo.emplace(this);
            }
        }
    }

    if(animate){
        showTermbox = false;
    }else{
        OnClick();
        OnHover();
    }

    //DEBUG
    if(InputHandler::GetKey() == SDLK_0){
        showLines = !showLines;
    }
    //DEBUG_PRINT("Setor::Update() - fim");
}

void Setor::LateUpdate(){
    if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED ||
       InputHandler::mouseMoved ){
        if(IsMouseInside()){
            sp.SetAlpha(SDL_ALPHA_OPAQUE);
        }else{
            if(hasClick == nullptr){
                sp.SetAlpha(SDL_ALPHA_OPAQUE*0.5);
            }else if(hasClick == this || hasClick->termo == termo){
                sp.SetAlpha(SDL_ALPHA_OPAQUE);
            }else if(hasClick != this){
                sp.SetAlpha(SDL_ALPHA_OPAQUE*0.2);
            }
        }
    }
}

void Setor::Animate(float dt){
    //se não é o setor selecionado
    if(hasClick != this){
        angS += diff;
    }else{//se for o setor selecionado

        double med = angS + angF/2;
        //if(med == STOP_ANGLE) animate = false;
        if(diff + med > STOP_ANGLE && //quando deve parar
        !(diff + med > STOP_ANGLE + 25) ){//tolerancia
            animate = false;
            diff = 0;
            //diff = STOP_ANGLE - med;
        }else{
            diff = ANIMATION_SPEED*dt;
            angS += diff;
        }
    }
    if(angS >= 360) angS -= 360;
}

void Setor::OnClick(){
    if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
        if(IsMouseInside()){
            hasClick = this;
            SelectSetor();
        }
        if(!IsMouseInside()){
            UnselectSetor();
        }
    }
}

void Setor::OnHover(){
    if(InputHandler::mouseMoved){
        if(IsMouseInside()){//MouseHover
            sp.SetAlpha(SDL_ALPHA_OPAQUE);
            if(hasClick != this){//se não for esse o setor clicado
                showTermbox = true;
            }
        }else{//se não está em MouseHover
                showTermbox = false;
        }
    }
}

void Setor::SelectSetor(){
    agl.SetorSelected();
    sp.SetAlpha(SDL_ALPHA_OPAQUE);

    double med = Setor::hasClick->angS + Setor::hasClick->angF/2;
    if(med < STOP_ANGLE || STOP_ANGLE < med){
        animate = true;
    }

    //Ao ser selecionado, o setor verifica se é
    //necessario limpar a lista de setores de mesmo termo
    if(!setoresTermo.empty() && (*setoresTermo.begin())->termo != termo){
        DEBUG_PRINT("Limpa lista de setores com mesmo termo");
        do{
            auto it = setoresTermo.begin();
            setoresTermo.erase(it);
        }while(!setoresTermo.empty());
    }
    if(setoresTermo.empty()) setoresTermo.emplace(this);
    Camera::Follow(agl.enquadramento);
}

void Setor::UnselectSetor(){
    agl.hasSectorSelected = false;
}

void Setor::UpdatePosition(float dt){
    //quando a animação está ligada e o aglomerado selecionado é o dono deste setor
    //Ao invés de cada setor calcular quando deve andar, será feito apenas um calculo
    //e todos serão atualizados a mesma quantidade fixa.
    if(animate && (&agl == agl.aglSelected) ){
        Animate(dt);
    }
    sp.SetX(agl.GetCenter().x + agl.GetRadius() + agl.setorDist);
    sp.SetY(agl.GetCenter().y);

    termSetor.SetX(termSetor.GetX() + agl.GetCenter().x);
    termSetor.SetY(termSetor.GetY() + agl.GetCenter().y);
    //Durante a animação as respostas ao mouse são desligadas

    //Arruma o posicionamento do termo em relação a posicao do setor
    double mediana = angS+angF/2;
    if(0 < mediana && mediana <= 90){//primeiro quadrante
        termBox.SetPosition(agl.GetCenter().x+(agl.GetRadius()+agl.setorDist+sp.GetWidth())*cos( mediana *PI/180),
                            agl.GetCenter().y+(agl.GetRadius()+agl.setorDist+sp.GetWidth())*sin( mediana *PI/180));

        termSetor.SetPos(agl.GetCenter().x+(agl.GetRadius()+agl.setorDist+sp.GetWidth())*cos( mediana *PI/180),
                         agl.GetCenter().y+(agl.GetRadius()+agl.setorDist+sp.GetWidth())*sin( mediana *PI/180));

    }else if(90 < mediana && mediana <= 180){//segundo quadrante
        termBox.SetPosition(agl.GetCenter().x - termBox.GetWidth() +(agl.GetRadius()+agl.setorDist+sp.GetWidth())*cos( mediana *PI/180),
                            agl.GetCenter().y +(agl.GetRadius()+agl.setorDist+sp.GetWidth())*sin( mediana *PI/180));

        termSetor.SetPos(agl.GetCenter().x - termBox.GetWidth() +(agl.GetRadius()+agl.setorDist+sp.GetWidth())*cos( mediana *PI/180),
                         agl.GetCenter().y +(agl.GetRadius()+agl.setorDist+sp.GetWidth())*sin( mediana *PI/180));

    }else if(180 < mediana && mediana <= 270){
        termBox.SetPosition(agl.GetCenter().x - termBox.GetWidth() +(agl.GetRadius()+agl.setorDist+sp.GetWidth())*cos( mediana *PI/180),
                            agl.GetCenter().y - termBox.GetHeight() +(agl.GetRadius()+agl.setorDist+sp.GetWidth())*sin( mediana *PI/180));

        termSetor.SetPos(agl.GetCenter().x - termBox.GetWidth() +(agl.GetRadius()+agl.setorDist+sp.GetWidth())*cos( mediana *PI/180),
                         agl.GetCenter().y - termBox.GetHeight() +(agl.GetRadius()+agl.setorDist+sp.GetWidth())*sin( mediana *PI/180));

    }else if(270 < mediana && mediana <= 360){
        termBox.SetPosition(agl.GetCenter().x +(agl.GetRadius()+agl.setorDist+sp.GetWidth())*cos( mediana *PI/180),
                            agl.GetCenter().y - termBox.GetHeight() +(agl.GetRadius()+agl.setorDist+sp.GetWidth())*sin( mediana *PI/180));

        termSetor.SetPos(agl.GetCenter().x +(agl.GetRadius()+agl.setorDist+sp.GetWidth())*cos( mediana *PI/180),
                         agl.GetCenter().y - termBox.GetHeight() +(agl.GetRadius()+agl.setorDist+sp.GetWidth())*sin( mediana *PI/180));
    }
}

void Setor::SetPercent(double percent){
    this->percent = percent;
}

void Setor::SetAng(double ang){
    this->angS = ang;
    this->angF = 360*percent + angS;
}

bool Setor::IsMouseInside(){
    double dist = agl.GetCenter().DistTo(InputHandler::GetMousePosition().x, InputHandler::GetMousePosition().y);
    //angulo em graus
    double angle = (180/PI) * agl.GetCenter().AngleTo(InputHandler::GetMousePosition().x, InputHandler::GetMousePosition().y);
    if(dist <= agl.GetRadius() + sp.GetWidth() + agl.setorDist &&
       dist >= agl.GetRadius() + agl.setorDist){
           if(( angS <= angle && angle <= angS + angF) ||
              ( angS <= (angle + 360) && (angle + 360) <= angS + angF)){
                   return true;
            } else return false;
    }else return false;
}

void Setor::NewAngle(int totalTermos){
    angF = 360* quantTermos/totalTermos;
}

string Setor::GetPostPath(PostSelected tab){
    return posts[tab];
}

void Setor::SetAlpha(int alpha){
    sp.SetAlpha(alpha);
}

void Setor::Shrink(float percent){
    SDL_Point pt;
    pt.x = - agl.GetRadius() - agl.setorDist;
    pt.y = 0;
    sp.SetRotationPoint(pt);
    sp.Resize(sp.GetWidth()*percent, sp.GetHeight()*percent);
}

set<Setor*>& Setor::GetSetorSet(){
    return setoresTermo;
}

void Setor::ShowLines(){
            SDL_SetRenderDrawColor(Window::GetRenderer(),0,0,0,SDL_ALPHA_OPAQUE);

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

            SDL_SetRenderDrawColor(Window::GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
            Point pt1(agl.GetCenter().x + agl.GetRadius()*cos(angS*PI/180),
                      agl.GetCenter().y + agl.GetRadius()*sin(angS*PI/180));
            Point pt2(agl.GetCenter().x + agl.GetRadius()*cos( (angS+angF)*PI/180 ),
                      agl.GetCenter().y + agl.GetRadius()*sin( (angS+angF)*PI/180));
            SDL_RenderDrawLine(Window::GetRenderer(), agl.GetCenter().x, agl.GetCenter().y, pt1.x, pt1.y);
            SDL_RenderDrawLine(Window::GetRenderer(), agl.GetCenter().x, agl.GetCenter().y, pt2.x, pt2.y);

}

Aglutinado& Setor::GetAgl(){
    return agl;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

#include "Relacao.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
#endif //DEBUG

Relacao::Relacao(Aglutinado& aglut1, Aglutinado& aglut2, int forca):
    aglut1(aglut1),
    aglut2(aglut2),
    forca(forca),
    retangulo(nullptr),
    showDebug(false),
    i(0)
{
    DEBUG_PRINT("Relacao " << this << " entre " << &aglut1 << " e " << &aglut2);
    pt.x = (aglut1.GetFixedCenter().x + aglut2.GetFixedCenter().x)/2;
    pt.y = (aglut1.GetFixedCenter().y + aglut2.GetFixedCenter().y)/2;
    if(forca > 1){
        int dist = aglut1.GetCenter().DistTo(aglut2.GetCenter());
        DEBUG_PRINT("Raio de aglut1 == " << &aglut1 << ": " <<  aglut1.GetRadiusExternal());
        DEBUG_PRINT("Raio de aglut2 == " << &aglut2 << ": " <<  aglut2.GetRadiusExternal());

        if(retangulo == nullptr){
            retangulo = new Sprite("img/Setores/relacao.png", aglut1.GetCenter().x + aglut1.GetRadiusExternal(), aglut1.GetCenter().y - forca);
        }
        retangulo->Resize(dist - (aglut1.GetRadiusExternal() + aglut2.GetRadiusExternal() ),forca*2);

        SDL_Point rotationPoint;
        rotationPoint = {aglut1.GetCenter().x, aglut1.GetCenter().y};
        DEBUG_PRINT("ponto de rotacao: " << rotationPoint.x << "x" << rotationPoint.y);
        retangulo->SetRotationPoint(rotationPoint);
        //retangulo->SetRotationAngle(aglut1.GetCenter().AngleTo( aglut2.GetCenter())*180/PI);
    }
}

Relacao::~Relacao()
{
    //dtor
}
void Relacao::AddTermo(string termo){
    termos.push_back(new Text("fonts/Roboto-Regular.ttf", 10, BLENDED, termo, 0, 0, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE));
    if(termos.size() == 1){
        termos.back()->SetPos(pt.x, pt.y);
    }else if(termos.size() > 1){
        termos.back()->SetPos(pt.x, pt.y + (termos.size()-1)*termos.back()->GetHeight());
    }
}

void Relacao::PrintTermos(){
    for(int i = 0; i < termos.size(); i++){
        cout << termos[i]->GetText() << endl;
    }
}

void Relacao::Update(float dt){
    if(forca > 1){
//        retangulo->SetRotationAngle(i++);
//        if(i > 360) i -=360;
    }
    //DEBUG
    if(InputHandler::GetKey() == SDLK_0){
        showDebug = true;
    }
}

void Relacao::Render(){
    for(int i = 0; i < termos.size(); i++){
        termos[i]->Render();
    }
    SDL_SetRenderDrawColor(Window::GetRenderer(), 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE);
    float cosThisOther = cos(aglut1.GetCenter().AngleTo( aglut2.GetCenter()));
    float sinThisOther = sin(aglut1.GetCenter().AngleTo( aglut2.GetCenter()));

    float cosOtherThis = cos( aglut2.GetCenter().AngleTo(aglut1.GetCenter()));
    float sinOtherThis = sin( aglut2.GetCenter().AngleTo(aglut1.GetCenter()));

    if(forca == 1){
        SDL_RenderDrawLine(Window::GetRenderer(),
                           aglut1.GetCenter().x + aglut1.GetRadiusExternal()*cosThisOther,
                           aglut1.GetCenter().y + aglut1.GetRadiusExternal()*sinThisOther,
                           aglut2.GetCenter().x + aglut2.GetRadiusExternal()*cosOtherThis,
                           aglut2.GetCenter().y + aglut2.GetRadiusExternal()*sinOtherThis);
    }else{
        retangulo->Render();
    }

    //DEBUG
    if(showDebug){
        SDL_SetRenderDrawColor(Window::GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawPoint(Window::GetRenderer(), pt.x, pt.y);

        SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawPoint(Window::GetRenderer(), aglut1.GetCenter().x, aglut1.GetCenter().y);
    }
}

void Relacao::RePosition(Aglutinado* agl){
    if(forca > 1){
        if(agl == &aglut1){
            retangulo->SetPosition(aglut1.GetCenter().x + aglut1.GetRadiusExternal(), aglut1.GetCenter().y - forca);
            retangulo->SetWidth( 2 + aglut1.GetCenter().DistTo(aglut2.GetCenter()) -
                                (aglut1.GetRadiusExternal()+aglut2.GetRadiusExternal()));
            SDL_Point rotationPoint;
            rotationPoint.x = -aglut1.GetRadiusExternal();
            rotationPoint.y = forca;
            retangulo->SetRotationPoint(rotationPoint);
            retangulo->SetRotationAngle( aglut1.GetCenter().AngleTo( aglut2.GetCenter())*180/PI);
        }
    }
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

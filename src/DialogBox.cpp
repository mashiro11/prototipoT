#include "DialogBox.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
#endif //DEBUG

bool DialogBox::transfer(false);

DialogBox::DialogBox(Aglutinado& agl, int x, int y, string bgFile, string fontFile, int fontSize, TextStyle style):
    agl(agl),
    posRel(x,y),
    showDBox(false),
    body(bgFile, agl.GetCenter().x + posRel.x, agl.GetCenter().y + posRel.y),
    buttonBack(BUTTON_BACK_PATH, body.GetX() + body.GetWidth()/2, body.GetY() + body.GetHeight()/2),
    buttonNext(BUTTON_NEXT_PATH, body.GetX() + body.GetWidth()/2, body.GetY() + body.GetHeight()/2),
    termo(fontFile, fontSize, style, " ", body.GetX(), body.GetY() + 10, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    verPosts(fontFile, 10, style, "ver publicações", body.GetX() + body.GetWidth()/2 , body.GetY() + body.GetHeight() - 20, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE ),
    quantSetores(fontFile, 10, style, " ", body.GetX() + body.GetWidth()/2 , body.GetY() + body.GetHeight() - 20, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE ),
    numSetores(0),
    post(nullptr),
    showPosts(false)
{
    //DialogBox agora vai ser uma classe separada de Aglutinado
    quantSetores.SetY(body.GetY() + body.GetHeight()/2);

    buttonBack.Resize(buttonBack.GetWidth()/2, buttonBack.GetHeight()/2);
    buttonNext.Resize(buttonNext.GetWidth()/2, buttonNext.GetHeight()/2);

    buttonBack.SetPosition(body.GetX() + body.GetWidth()/2 - buttonBack.GetWidth(), body.GetY() + body.GetHeight()/2);
    buttonNext.SetPosition(body.GetX() + body.GetWidth()/2, body.GetY() + body.GetHeight()/2);

    //CentralizeText(verPosts);
    //ctor
}

DialogBox::~DialogBox()
{
    //dtor
}

void DialogBox::Render(){
    //DEBUG_PRINT("DialogBox::Render - inicio");
    if(showDBox){
        body.Render();
        termo.Render();
        verPosts.Render();
        buttonBack.Render();
        quantSetores.Render();
        buttonNext.Render();
        if(post != nullptr && showPosts){
            post->Render();
        }
    }
    //DEBUG_PRINT("DialogBox::Render - fim");
}

void DialogBox::Update(float dt){
    //DEBUG_PRINT("DialogBox::Update() - inicio");
    if(showDBox && !IsMouseInside() && InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED ){
        Close();
    }
    if(!showDBox && agl.hasSectorSelected){
        Open();
    }
//    if(Setor::hasClick != nullptr && Setor::hasClick->termo != termo.GetText()){
//        ChangeTermo();
//    }
    if(showDBox){
        UpdatePosition(dt);
        OnClick();
        OnHover();
        OnMouseRoll();
    }
    //DEBUG_PRINT("DialogBox::Update() - fim");
}

void DialogBox::UpdatePosition(float dt){
    if(Camera::cameraMove){
        body.SetX(posRel.x + agl.GetCenter().x);
        body.SetY(posRel.y + agl.GetCenter().y);

        termo.SetX(body.GetX() + body.GetWidth()/2 - termo.GetWidth()/2);
        termo.SetY(body.GetY() + 10);

        verPosts.SetX(body.GetX() + body.GetWidth()/2 - verPosts.GetWidth()/2 );
        verPosts.SetY(body.GetY() + body.GetHeight() - 20);


        quantSetores.SetPos(body.GetX() + body.GetWidth()/2 - quantSetores.GetWidth()/2,
                            body.GetY() + body.GetHeight()/2 + buttonBack.GetHeight()/2 - quantSetores.GetHeight()/2);

        buttonBack.SetPosition(quantSetores.GetX() - buttonBack.GetWidth()*1.5,
                               body.GetY() + body.GetHeight()/2);

        buttonNext.SetPosition(quantSetores.GetX() + quantSetores.GetWidth()*1.5,
                               body.GetY() + body.GetHeight()/2);
        if(post != nullptr){
            post->SetPosition(body.GetX() + body.GetWidth(), body.GetY());
        }
    }
}

void DialogBox::LateUpdate(){
    if(Setor::hasClick != nullptr &&
       Setor::hasClick->termo != termo.GetText()){
        ChangeTermo();
    }
    if(numSetores != Setor::setoresTermo.size()){
        SetQuantSetores();
    }
}

void DialogBox::OnClick(){
    if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
        if(verPosts.IsMouseInside()){
            showPosts = !showPosts;
            if(showPosts){
                verPosts.SetText("esconder publicações");
            }else{
                verPosts.SetText("ver publicações");
            }
            verPosts.SetX(body.GetX() + body.GetWidth()/2 - verPosts.GetWidth()/2);
        }
        if(buttonBack.IsMouseInside() || buttonNext.IsMouseInside()){
            transfer = true;
            Close();
            Setor::hasClick->UnselectSetor();
            if(buttonBack.IsMouseInside()){
                //se for o primeiro, vai para o ultimo
                if( Setor::GetSetorSet().find(Setor::hasClick) != Setor::GetSetorSet().begin() ){
                    Setor::hasClick = (*(--(Setor::GetSetorSet().find(Setor::hasClick))));
                }else{
                    Setor::hasClick = (*(--(Setor::GetSetorSet().end())));
                }
            }
            if(buttonNext.IsMouseInside()){
                //se for o ultimo, vai para o primeiro
                if( Setor::GetSetorSet().find(Setor::hasClick) != --(Setor::GetSetorSet().end())){
                    Setor::hasClick = (*(++(Setor::GetSetorSet().find(Setor::hasClick))));
                }else{
                    Setor::hasClick = *(Setor::GetSetorSet().begin());
                }
            }
            Setor::hasClick->SelectSetor();
        }else{
            transfer = false;
        }
    }
}

void DialogBox::OnHover(){
    if(InputHandler::mouseMoved){

    }
}

void DialogBox::OnMouseRoll(){
    if(InputHandler::mouseScroll){
        if(post != nullptr && post->IsMouseInside()){
            Camera::cameraScroll = false;
            post->SlideClip(0, InputHandler::GetMouseScrollY()*SCROLL_SPEED);
        }else if(post != nullptr && !post->IsMouseInside()){
            Camera::cameraScroll = true;
        }
    }
}

void DialogBox::SetTermo(string termo){
    //if(termo != this->termo.GetText()){
        this->termo.SetText(termo);
        this->termo.SetX(body.GetX() + body.GetWidth()/2 - this->termo.GetWidth()/2);
//        this->buttonBack.SetX(quantSetores.GetX() - buttonBack.GetWidth()*1.5);
//        this->buttonNext.SetX(quantSetores.GetX() + quantSetores.GetWidth()*1.5);
    //}
}

void DialogBox::SetQuantSetores(){
    numSetores = Setor::setoresTermo.size();
    this->quantSetores.SetText(to_string(1) + " de " + to_string(numSetores) );
    this->quantSetores.SetX(body.GetX() + body.GetWidth()/2 - this->quantSetores.GetWidth()/2);
}

void DialogBox::Open(){
    showDBox = true;
    ChangeTermo();
}

void DialogBox::ChangeTermo(){
    //termoTemp = Setor::hasClick->termo;
    SetTermo(Setor::hasClick->termo);
    //informa qual imagem de post deve ser renderizada
    SetPost(Setor::hasClick->GetPostPath());
}

void DialogBox::Close(){
    showDBox = showPosts = false;
    verPosts.SetText("ver publicações");
    verPosts.SetX(body.GetX() + body.GetWidth()/2 - verPosts.GetWidth()/2);
    RemovePost();
}

void DialogBox::SetPost(string post, int x, int y){
    if(this->post != nullptr) delete this->post;
    this->post = new Sprite(post, body.GetX() + body.GetWidth() + x , body.GetY() + y );
    this->post->Clip(this->post->GetWidth(), 500);
    this->post->Resize(this->post->GetWidth(), 500);
}

void DialogBox::RemovePost(){
    if(this->post != nullptr) delete this->post;
    this->post = nullptr;
}

int DialogBox::GetWidth(){
    return body.GetWidth();
}

void DialogBox::CentralizeText(Text text){
    text.SetX(body.GetWidth()/2 + body.GetX() - text.GetWidth()/2);
}

bool DialogBox::IsMouseInside(){
    bool cumulativeCondition = false;
    cumulativeCondition |= body.IsMouseInside();
    cumulativeCondition |= agl.IsMouseInsideExternalRadius();
    return cumulativeCondition;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

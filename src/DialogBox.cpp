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
bool DialogBox::showPosts(false);
bool DialogBox::showDBox(false);
DialogBox* DialogBox::instance = nullptr;

//Sprite DialogBox::body(WINDOW_BOX_PATH);
//Sprite DialogBox::buttonBack(BUTTON_BACK_PATH, body.GetX() + body.GetWidth()/2, body.GetY() + body.GetHeight()/2);
//Sprite DialogBox::buttonNext(BUTTON_NEXT_PATH, body.GetX() + body.GetWidth()/2, body.GetY() + body.GetHeight()/2);
//Text DialogBox::termo("fonts/Roboto-Bold.ttf", 20, BLENDED, " ", body.GetX(), body.GetY() + 10, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE);
//Text DialogBox::verPosts("fonts/Roboto-Bold.ttf", 10, BLENDED, "ver publicações", body.GetX() + body.GetWidth()/2 , body.GetY() + body.GetHeight() - 20, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE );
//Text DialogBox::quantSetores("fonts/Roboto-Bold.ttf", 10, BLENDED, " ", body.GetX() + body.GetWidth()/2 , body.GetY() + body.GetHeight() - 20, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE );

DialogBox::DialogBox():
    body(WINDOW_BOX_PATH),
    buttonBack(BUTTON_BACK_PATH, body.GetX() + body.GetWidth()/2, body.GetY() + body.GetHeight()/2),
    buttonNext(BUTTON_NEXT_PATH, body.GetX() + body.GetWidth()/2, body.GetY() + body.GetHeight()/2),
    termo("fonts/Roboto-Bold.ttf", 20, BLENDED, " ", body.GetX(), body.GetY() + 10, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    verPosts("fonts/Roboto-Bold.ttf", 10, BLENDED, "ver publicações", body.GetX() + body.GetWidth()/2 , body.GetY() + body.GetHeight() - 20, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE ),
    quantSetores("fonts/Roboto-Bold.ttf", 10, BLENDED, " ", body.GetX() + body.GetWidth()/2 , body.GetY() + body.GetHeight() - 20, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE ),
    posRel(0,0),
    numSetores(0),
    post(nullptr)
{
}

DialogBox& DialogBox::GetInstance(){
    if(instance == nullptr){
        instance = new DialogBox();
    }
    return *instance;
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
    if(!showDBox &&
       Aglutinado::aglSelected->hasSectorSelected){
        Open();
        if(posRel.x == 0 && posRel.y == 0){
            posRel.x = Aglutinado::aglSelected->GetRadiusExternal()/2;
            posRel.y -= Aglutinado::aglSelected->GetRadiusExternal()/2;
        }
    }
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
        body.SetX(posRel.x + Aglutinado::aglSelected->GetCenter().x);
        body.SetY(posRel.y + Aglutinado::aglSelected->GetCenter().y);

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
        DEBUG_PRINT("Houve um click");
        DEBUG_PRINT("IsMouseInside: " << IsMouseInside());
        if(!IsMouseInside()){
            DEBUG_PRINT("fora de DialogBox");
            Close();
        }else{
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
                //Close();
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
        DialogBox::termo.SetText(termo);
        DialogBox::termo.SetX(body.GetX() + body.GetWidth()/2 - DialogBox::termo.GetWidth()/2);
//        this->buttonBack.SetX(quantSetores.GetX() - buttonBack.GetWidth()*1.5);
//        this->buttonNext.SetX(quantSetores.GetX() + quantSetores.GetWidth()*1.5);
    //}
}

void DialogBox::SetQuantSetores(){
    numSetores = Setor::setoresTermo.size();
    quantSetores.SetText(to_string(1) + " de " + to_string(numSetores) );
    quantSetores.SetX(body.GetX() + body.GetWidth()/2 - quantSetores.GetWidth()/2);
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
    if(DialogBox::post != nullptr) delete DialogBox::post;
    DialogBox::post = new Sprite(post, body.GetX() + body.GetWidth() + x , body.GetY() + y );
    DialogBox::post->Clip(DialogBox::post->GetWidth(), 500);
    DialogBox::post->Resize(DialogBox::post->GetWidth(), 500);
}

void DialogBox::RemovePost(){
    if(post != nullptr) delete post;
    post = nullptr;
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
    if(Aglutinado::aglSelected != nullptr){
        cumulativeCondition |= Aglutinado::aglSelected->IsMouseInsideExternalRadius();
    }
    return cumulativeCondition;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

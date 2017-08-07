#include "DialogBox.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
#endif //DEBUG

DialogBox::DialogBox(Aglutinado& agl, int x, int y, string bgFile, string fontFile, int fontSize, TextStyle style):
    agl(agl),
    posRel(x,y),
    showDBox(false),
    body(bgFile, agl.GetCenter().x + posRel.x, agl.GetCenter().y + posRel.y),
    buttonBack(BUTTON_BACK_PATH, body.GetX() + body.GetWidth()/2, body.GetY() + body.GetHeight()/2),
    buttonNext(BUTTON_NEXT_PATH, body.GetX() + body.GetWidth()/2, body.GetY() + body.GetHeight()/2),
    termo(fontFile, fontSize, style, " ", body.GetX(), body.GetY() + 10, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    verPosts(fontFile, 10, style, "ver publicações", body.GetX() + body.GetWidth()/2 , body.GetY() + body.GetHeight() - 20, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE ),
    post(nullptr),
    showPosts(false)
{
    buttonBack.Resize(buttonBack.GetWidth()/2, buttonBack.GetHeight()/2);
    buttonNext.Resize(buttonNext.GetWidth()/2, buttonNext.GetHeight()/2);

    buttonBack.SetPosition(body.GetX() + body.GetWidth()/2 - buttonBack.GetWidth(), body.GetY() + body.GetHeight()/2);
    buttonNext.SetPosition(body.GetX() + body.GetWidth()/2, body.GetY() + body.GetHeight()/2);

    body.Resize(body.GetWidth(), 35);

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
        buttonNext.Render();
        if(post != nullptr && showPosts){
            post->Render();
        }
    }
    //DEBUG_PRINT("DialogBox::Render - fim");
}

void DialogBox::Update(float dt){
    if(showDBox){
        body.SetX(posRel.x + agl.GetCenter().x);
        body.SetY(posRel.y + agl.GetCenter().y);

        termo.SetX(body.GetX());
        termo.SetY(body.GetY() + 10);

        verPosts.SetX(body.GetX() + body.GetWidth()/2 );
        verPosts.SetY(body.GetY() + body.GetHeight() - 20);

        buttonBack.SetPosition(body.GetX() + body.GetWidth()/2 - buttonBack.GetWidth(),
                               body.GetY() + body.GetHeight()/2);
        buttonNext.SetPosition(body.GetX() + body.GetWidth()/2,
                               body.GetY() + body.GetHeight()/2);

        if(post != nullptr){
            post->SetPosition(body.GetX() + body.GetWidth(), body.GetY());
        }

        if(body.GetHeight() == 35){
            body.SetHeight(165);
        }
        if(verPosts.IsMouseInside() && InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
            showPosts = true;
        }
        if(post != nullptr && post->IsMouseInside()){
            Camera::cameraScroll = false;
            post->SlideClip(0, InputHandler::GetMouseScrollY()*SCROLL_SPEED);
        }else if(post != nullptr && !post->IsMouseInside()){
            Camera::cameraScroll = true;
        }
    }
}

void DialogBox::SetTermo(string termo){
    //DEBUG_PRINT("DialogBox::SetTermo() - inicio");
    this->termo.SetText(termo);
    //CentralizeText(this->termo);
    //DEBUG_PRINT("DialogBox::SetTermo() - fim");
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
    return body.IsMouseInside();
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

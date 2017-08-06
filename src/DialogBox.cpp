#include "DialogBox.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
#endif //DEBUG

DialogBox::DialogBox(int x, int y, string bgFile, string fontFile, int fontSize, TextStyle style):
    showDBox(false),
    body(bgFile, x, y),
    buttonBack(BUTTON_BACK_PATH, x + body.GetWidth()/2, y + body.GetHeight()/2),
    buttonNext(BUTTON_NEXT_PATH, x + body.GetWidth()/2, y + body.GetHeight()/2),
    termo(fontFile, fontSize, style, " ", x, y + 10, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE),
    verPosts(fontFile, 10, style, "ver publica��es", x + body.GetWidth()/2 , y + body.GetHeight() - 20, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE ),
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

void DialogBox::Update(){
    if(showDBox){
        if(body.GetHeight() == 35){
            body.SetHeight(165);
        }
        if(verPosts.IsMouseInside() && InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
            showPosts = true;
        }
        if(post != nullptr && post->IsMouseInside()){
            post->SlideClip(0, InputHandler::GetMouseScrollY()*SCROLL_SPEED);
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
    this->post = new Sprite(post, body.GetX() + x , body.GetY() + y );
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

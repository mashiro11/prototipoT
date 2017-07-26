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
    body(bgFile, x, y),
    termo(fontFile, fontSize, style, "a", x, y),
    verPosts(fontFile, 10, style, "ver publicações", x , y + body.GetHeight() - 20, 0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE ),
    post(nullptr)
{
    //ctor
}

DialogBox::~DialogBox()
{
    //dtor
}

void DialogBox::Render(){
    //DEBUG_PRINT("DialogBox::Render - inicio");
    body.Render();
    termo.Render();
    verPosts.Render();
    if(post != nullptr){
        post->Render();
    }
    //DEBUG_PRINT("DialogBox::Render - fim");
}

void DialogBox::Update(){
//    if(InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED && !IsMouseInside()){
//        //posts.Clip(posts.GetWidth(), posts.GetHeight(), 0, 0);
//        showPosts = false;
//    }
    if(post != nullptr && post->IsMouseInside()){
        post->SlideClip(0, InputHandler::GetMouseScrollY()*SCROLL_SPEED);
    }
}

void DialogBox::SetTermo(string termo){
    //DEBUG_PRINT("DialogBox::SetTermo() - inicio");
    this->termo.SetText(termo);
    this->termo.SetFontSize(10);
    this->termo.SetColor(0x69, 0xBA, 0xF7, SDL_ALPHA_OPAQUE);
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
#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

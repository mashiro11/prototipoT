#include "Sprite.h"

bool Sprite::imgInitiated = false;

Sprite::Sprite(string path, int x, int y)
{
    _Initiate();
    imgRect.x = x;
    imgRect.y = y;
    Open(path);
}

Sprite::~Sprite()
{

}
void Sprite::Open(string path){
    this->path = path;
    aux = IMG_Load(path.c_str());
    img = Resources::GetTexture(path);
    imgRect.w = aux->w;
    imgRect.h = aux->h;
    srcRect = {0,0,aux->w,aux->h};//como vai ser recortado na imagem
}

int Sprite::_Initiate(){
    if(!imgInitiated){
        if(!IMG_Init( IMG_INIT_PNG )){
            cout << "IMG_Init() error: " << IMG_GetError() << endl;
            return 4;
        }else{
            imgInitiated = true;
        }
    }
    return 0;
}

int Sprite::GetWidth(){
    return imgRect.w;
}

int Sprite::GetHeight(){
    return imgRect.h;
}

int Sprite::GetX(){
    return imgRect.x;
}

int Sprite::GetY(){
    return imgRect.y;
}

void Sprite::SetX(int x){
    imgRect.x = x;
}

void Sprite::SetY(int y){
    imgRect.y = y;
}

void Sprite::Clip(int w, int h, int x, int y){
    imgRect.w = srcRect.w = w;
    imgRect.h = srcRect.h = h;
    srcRect.x = x;
    srcRect.y = y;
}
void Sprite::Resize(int percentx, int percenty){
    if(percenty == 100){
        imgRect.w *= percentx/100.0;
        imgRect.h *= percentx/100.0;
    }else{
        imgRect.w *= percentx/100.0;
        imgRect.h *= percenty/100.0;
    }
}

void Sprite::Render(int x, int y){
    //como vai aparecer na tela
    if(SDL_RenderCopyEx(Window::GetRenderer(), img, &srcRect, &imgRect, 0, NULL, SDL_FLIP_NONE)){
                cout << "SDL_RenderCopyEx() error: " << SDL_GetError() << endl;
        }
}

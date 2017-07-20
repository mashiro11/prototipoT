#include "Sprite.h"

Sprite::Sprite(string path, int x, int y)
{
    imgRect.x = x;
    imgRect.y = y;
    Open(path);
    angle = 0;
}

Sprite::~Sprite(){
}

void Sprite::Open(string path){
    this->path = path;
    aux = IMG_Load(path.c_str());
    img = Resources::GetTexture(path);
    imgRect.w = aux->w;
    imgRect.h = aux->h;
    srcRect = {0,0,aux->w,aux->h};//como vai ser recortado na imagem
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
void Sprite::Resize(int w, int h){
    imgRect.w = w;
    imgRect.h = h;
}

void Sprite::SetRotationPoint(SDL_Point pt){
    this->pt = pt;
}

void Sprite::SetRotationAngle(double angle){
    this->angle = angle;
}

void Sprite::Render(){
    //como vai aparecer na tela
    if(SDL_RenderCopyEx(Window::GetRenderer(), img, &srcRect, &imgRect, angle, &pt, SDL_FLIP_NONE)){
        cout << "SDL_RenderCopyEx() error: " << SDL_GetError() << endl;
    }
}

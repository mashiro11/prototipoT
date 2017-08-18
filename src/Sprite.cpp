#include "Sprite.h"

Sprite::Sprite(string path, int x, int y):
    alpha(SDL_ALPHA_OPAQUE),
    lastMouseInside(false),
    newMouseInside(false)
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

void Sprite::SetPosition(int x, int y){
    imgRect.x = x;
    imgRect.y = y;
}

void Sprite::SetX(int x){
    imgRect.x = x;
}

void Sprite::SetY(int y){
    imgRect.y = y;
}

void Sprite::SetHeight(int h){
    imgRect.h = h;
}

void Sprite::SetWidth(int w){
    imgRect.w = w;
}

void Sprite::SetAlpha(int alpha){
    this->alpha = alpha;
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

void Sprite::SetRotationAngle(int angle){
    this->angle = angle;
}

void Sprite::Update(float dt){
    lastMouseInside = newMouseInside;
    newMouseInside = IsMouseInside();
}

void Sprite::Render(){
    //como vai aparecer na tela
    if(alpha >= SDL_ALPHA_OPAQUE) alpha = SDL_ALPHA_OPAQUE;
    if(alpha <= SDL_ALPHA_TRANSPARENT) alpha = SDL_ALPHA_TRANSPARENT;
    if(SDL_SetTextureAlphaMod(this->img, alpha) < 0)
        SDL_GetError();

    SDL_SetTextureBlendMode(img, SDL_BLENDMODE_BLEND );

//    SDL_Rect temp = {imgRect.x + Camera::position.x,
//                     imgRect.y + Camera::position.y,
//                     imgRect.w, imgRect.h};
    if(SDL_RenderCopyEx(Window::GetRenderer(), img, &srcRect, &imgRect, (double)angle, &pt, SDL_FLIP_NONE)){
        cout << "SDL_RenderCopyEx() error: " << SDL_GetError() << endl;
    }
}

void Sprite::Transform(int w, int h){
    if(w != -1) imgRect.w = w;
    if(h != -1) imgRect.h = h;
}

bool Sprite::IsMouseInside(){
    if(InputHandler::GetMousePosition().x >= imgRect.x && InputHandler::GetMousePosition().x <= imgRect.x + imgRect.w &&
       InputHandler::GetMousePosition().y >= imgRect.y && InputHandler::GetMousePosition().y <= imgRect.y + imgRect.h  ){
        return true;
    }else return false;
}

void Sprite::SlideClip(int amountX, int amountY){
    if(amountX != 0){
       if(srcRect.x + amountX > 0){
           if(srcRect.x + amountY < aux->w - imgRect.w ){
               srcRect.x += amountY;
            }else{
                srcRect.x = aux->w - imgRect.w;
            }
        }else{
            srcRect.x = 0;
        }
    }

    if(amountY != 0){
       if(srcRect.y + amountY > 0){
           if(srcRect.y + amountY < aux->h - imgRect.h ){
               srcRect.y += amountY;
            }else{
                srcRect.y = aux->h - imgRect.h;
            }
        }else{
            srcRect.y = 0;
        }
    }
}

string Sprite::GetPath(){
    return path;
}

bool Sprite::MouseLeaved(){
    return !newMouseInside && lastMouseInside;
}

SDL_Point& Sprite::GetRotationPoint(){
    return pt;
}

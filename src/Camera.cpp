#include "Camera.h"

Point Camera::position(0,0);
bool Camera::moved(false);
Camera::~Camera()
{
    //dtor
}

void Camera::Update(){
    if(InputHandler::GetKey() == SDLK_LEFT){
        position.x += 1;
    }
    if(InputHandler::GetKey() == SDLK_UP){
        position.y += 1;
    }
    if(InputHandler::GetKey() == SDLK_RIGHT){
        position.x -= 1;
    }
    if(InputHandler::GetKey() == SDLK_DOWN){
        position.y -= 1;
    }
}

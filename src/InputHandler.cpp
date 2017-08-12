#include "InputHandler.h"

MOUSE_LB_STATE InputHandler::mouseLButton = NO_MOUSE_EVENT;
SDL_KeyboardEvent* InputHandler::keyboardState = new SDL_KeyboardEvent();
bool InputHandler::keydown = false;
bool InputHandler::quitRequested = false;
bool InputHandler::mouseMoved(false);
SDL_Point InputHandler::mousePosition = {0,0};
SDL_Point InputHandler::pastMousePosition = {0,0};


bool InputHandler::mouseScroll = false;
SDL_MouseWheelEvent* InputHandler::mouseState = new SDL_MouseWheelEvent();

void InputHandler::Update(float dt){
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
        if(pastMousePosition.x != mousePosition.x ||
           pastMousePosition.y != mousePosition.y){
            mouseMoved = true;
            pastMousePosition.x = mousePosition.x;
            pastMousePosition.y = mousePosition.y;
        }else{
            mouseMoved = false;
        }

        SDL_Event e;
        int events = SDL_PollEvent(&e);
        switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            mouseLButton = MOUSE_LBUTTON_PRESSED;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseLButton = MOUSE_LBUTTON_RELEASED;
            break;
        case SDL_MOUSEWHEEL:
            mouseScroll = true;
            *mouseState = e.wheel;
            break;
        case SDL_QUIT:
            quitRequested = true;
        default:
            mouseLButton = NO_MOUSE_EVENT;
        }
        if(e.type == SDL_KEYDOWN){
                keydown = true;
                *keyboardState = e.key;
        }else{
            keydown = false;
        }
        if(e.type != SDL_MOUSEWHEEL){
            mouseScroll = false;
        }
}

MOUSE_LB_STATE InputHandler::GetMouseLBState(){
    return mouseLButton;
}

SDL_Point& InputHandler::GetMousePosition(){
    return mousePosition;
}

int InputHandler::GetKey(){
    if(keydown){
        return keyboardState->keysym.sym;
    }else{
        return -1;
    }
}

//int InputHandler::GetMouseY(){
//    int x, y;
//    SDL_GetMouseState(&x, &y);
//    return y;
//}

int InputHandler::GetMouseScrollY(){
    if(mouseScroll){
        return mouseState->y;
    }else{
        return 0;
    }
}

int InputHandler::GetMouseScrollX(){
    if(mouseScroll){
        return mouseState->x;
    }else{
        return 0;
    }
}

bool InputHandler::QuitRequested(){
    if(keyboardState->keysym.sym == SDLK_ESCAPE || quitRequested ) return true;
    else return false;
}

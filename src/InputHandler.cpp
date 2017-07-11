#include "InputHandler.h"

MOUSE_LB_STATE InputHandler::mouseLButton = NO_MOUSE_EVENT;
SDL_KeyboardEvent* InputHandler::keyboardState = new SDL_KeyboardEvent();
bool InputHandler::keydown = false;
bool InputHandler::quitRequested = false;

void InputHandler::Update(){
        SDL_Event e;
        int events = SDL_PollEvent(&e);
        switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            mouseLButton = MOUSE_LBUTTON_PRESSED;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseLButton = MOUSE_LBUTTON_RELEASED;
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
}

MOUSE_LB_STATE InputHandler::GetMouseLBState(){
    return mouseLButton;
}

int InputHandler::GetMouseX(){
    int x, y;
    SDL_GetMouseState(&x, &y);
    return x;
}

int InputHandler::GetKey(){
    if(keydown){
        return keyboardState->keysym.sym;
    }else{
        return -1;
    }
}

int InputHandler::GetMouseY(){
    int x, y;
    SDL_GetMouseState(&x, &y);
    return y;
}

bool InputHandler::QuitRequested(){
    if(keyboardState->keysym.sym == SDLK_ESCAPE || quitRequested ) return true;
    else return false;
}

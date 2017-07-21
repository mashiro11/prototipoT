#include "../include/Window.h"

SDL_Window* Window::window = nullptr;
SDL_Renderer* Window::renderer = nullptr;
SDL_Surface* Window::screenSurface = nullptr;

int Window::Start(string nome, int w, int h, int x, int y)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL_Init() error: " << SDL_GetError() << endl;
        return 1;
    }

    window = SDL_CreateWindow(nome.c_str(), x, y, w, h, SDL_WINDOW_SHOWN );
    if(!window){
        cout << "SDL_CreateWindow() error: " << SDL_GetError() << endl;
        return 2;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        cout << "SDL_CreateRenderer() error: " << SDL_GetError() << endl;
        return 3;
    }
    screenSurface = SDL_GetWindowSurface(window);
    //verificação surface

    if(!IMG_Init( IMG_INIT_PNG )){
        cout << "IMG_Init() error: " << IMG_GetError() << endl;
            return 4;
    }

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

SDL_Window* Window::GetWindow(){
    return window;
}

SDL_Renderer* Window::GetRenderer(){
    return renderer;
}

void Window::Render(){
    SDL_RenderPresent(renderer);
}

void Window::Finish(){
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::Clear(){
    SDL_SetRenderDrawColor(renderer, 0x5C,0x94,0xFC,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

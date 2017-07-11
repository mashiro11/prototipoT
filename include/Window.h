#ifndef WINDOW_H
#define WINDOW_H


#define GRID_W_H 32
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600


#include <iostream>
#include <SDL.h>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Window
{
    public:
        //Window();
        //virtual ~Window();
        static int Start(string nome, int w = WINDOW_WIDTH, int h = WINDOW_HEIGHT,
                          int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED);
        static SDL_Renderer* GetRenderer();
        static SDL_Window* GetWindow();
        static void Render();
        static void Finish();
        static void Clear();
    protected:

    private:
        static SDL_Window *window;
        static SDL_Renderer *renderer;
        static SDL_Surface* screenSurface;
};

#endif // WINDOW_H

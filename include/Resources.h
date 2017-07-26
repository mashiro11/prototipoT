#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <sstream>
#include <memory>//unique_ptr
#include <unordered_map>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Window.h"

using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::stringstream;

class Resources
{
    public:
        static SDL_Texture* GetTexture(string path);
        static TTF_Font* GetFont(string file, int fontSize);
        virtual ~Resources();

    protected:

    private:
        typedef unordered_map< string , SDL_Texture*> SpriteIndex;
        typedef unordered_map< string, TTF_Font*> FontTable;


        static SpriteIndex sprites;
        static FontTable fonts;
};

#endif // RESOURCES_H

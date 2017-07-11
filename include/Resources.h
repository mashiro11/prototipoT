#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <memory>//unique_ptr
#include <unordered_map>
#include <SDL_image.h>


#include "Window.h"
//#include "MapObject.h"


using std::string;
using std::unique_ptr;
using std::unordered_map;

class Resources
{
    public:
        static SDL_Texture* GetTexture(string path);
        virtual ~Resources();

    protected:

    private:
        typedef unordered_map< string , SDL_Texture*> SpriteIndex;
        static SpriteIndex sprites;
};

#endif // RESOURCES_H

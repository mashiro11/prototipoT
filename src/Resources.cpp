#include "Resources.h"

unordered_map<string, SDL_Texture*> Resources::sprites;

SDL_Texture* Resources::GetTexture(string path){
    SpriteIndex::iterator got = sprites.find(path);
    if(got == sprites.end()){
        SDL_Texture* tx = IMG_LoadTexture(Window::GetRenderer(), path.c_str());
        if(!tx){
            cout << "IMG_LoadTexture() error: " << IMG_GetError() << endl;
        }else{
            sprites.emplace(path, tx);
        }

    }
    return sprites[path];
}

#include "Resources.h"

unordered_map<string, SDL_Texture*> Resources::sprites;
unordered_map<string, TTF_Font*> Resources::fonts;


SDL_Texture* Resources::GetTexture(string path){
    SpriteIndex::iterator got = sprites.find(path);
    if(got == sprites.end()){
        SDL_Texture* tx = IMG_LoadTexture(Window::GetRenderer(), path.c_str());
        if(!tx){
            cout << "Couldn't open " << path << ":" << endl;
            cout << "   IMG_LoadTexture() error: " << IMG_GetError() << endl;
        }else{
            sprites.emplace(path, tx);
        }

    }
    return sprites[path];
}

TTF_Font* Resources::GetFont(string file, int fontSize){
    stringstream chave;
    chave << file << fontSize;
    unordered_map<string, TTF_Font*>::const_iterator indice = fonts.find(chave.str());

    if (indice == fonts.end()){
        TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
        fonts.emplace(chave.str(), font);
        return font;
    } else {
        return indice->second;
    }
    return nullptr;
}


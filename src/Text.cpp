#include "Text.h"

//#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
#endif //DEBUG

bool Text::Initialized = false;

Text::Text(std::string fontFile, int fontSize, TextStyle style, std::string text, int x, int y, SDL_Color color)
{
    if(!Initialized){
        Initialize();
    }

	this->box.x = x;
	this->box.y = y;

	this->fontSize = fontSize;
	this->style = style;
	this->text = text;
	this->color = color;
	this->texture = nullptr;
//	fontFile = std::to_string(fontSize) + fontFile;
	this->font = Resources::GetFont(fontFile, fontSize);
	this->fontFile = fontFile;

	RemakeTexture();
}

Text::Text(std::string fontFile, int fontSize, TextStyle style, std::string text, int x, int y, int r, int g, int b, int a)
{
    SDL_Color cor = {r, g, b, a};
    if(!Initialized){
        Initialize();
    }

	this->box.x = x;
	this->box.y = y;

	this->fontSize = fontSize;
	this->style = style;
	this->text = text;
	this->color = cor;
	this->texture = nullptr;
	this->font = Resources::GetFont(fontFile, fontSize);
	this->fontFile = fontFile;

	RemakeTexture();
}

void Text::Initialize(){
    if( TTF_Init() != 0 ){
            cout << endl << "Problema no construtor de Game: TTF_Init() retornou diferente de zero" << endl;
            cout << SDL_GetError() << endl;
        }
    Initialized = true;
}

Text::~Text(){
    DEBUG_PRINT("begin TEXT DESTRUCTOR for ")
	if(this->texture)
		SDL_DestroyTexture(this->texture);
    DEBUG_PRINT("end TEXT destructor")
}

void Text::Render(){
	SDL_Rect dstRect;
	dstRect.x = this->box.x;
	dstRect.y = this->box.y;
	dstRect.w = this->box.w;
	dstRect.h = this->box.h;

	if(this->texture)
		SDL_RenderCopy(Window::GetRenderer(), this->texture, NULL, &dstRect);
}

void Text::SetPos(int x, int y, bool centerX, bool centerY){
	if(centerX)
		this->box.x = x - this->box.w/2.0; // arrumar calculo do centro
	else
		this->box.x = x;
	if(centerY)
		this->box.y = y - this->box.h/2.0;
	else
		this->box.y = y;

	RemakeTexture();
}

void Text::SetX(int x, bool centered){
    if(centered)
		this->box.x = x - this->box.w/2.0; // arrumar calculo do centro
	else
		this->box.x = x;

    RemakeTexture();
}

void Text::SetY(int y, bool centered){
    if(centered)
		this->box.y = y - this->box.h/2.0; // arrumar calculo do centro
	else
		this->box.y = y;

    RemakeTexture();
}

void Text::SetColor(SDL_Color color){
	this->color = color;
	RemakeTexture();
}

void Text::SetColor(int r, int g, int b, int a){
    SDL_Color color = {r, g, b, a};
    SetColor(color);
}

void Text::SetStyle(TextStyle style){
	this->style = style;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize){
	this->fontSize = fontSize;
//	std::string str_fontSize = to_string(fontSize);
//	fontFile[0] = str_fontSize[0];
//	fontFile[1] = str_fontSize[1];
	RemakeTexture();
}

void Text::SetText(std::string text){
    this->text = text;
    RemakeTexture();
}

void Text::RemakeTexture(){
	this->font = Resources::GetFont(fontFile, fontSize);

	SDL_DestroyTexture(this->texture);
	SDL_Surface* surface;

	if(this->style == SOLID)
		surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
	if(this->style == SHADED)
		surface = TTF_RenderText_Shaded(this->font, this->text.c_str(), this->color, TEXT_BLACK);
	if(this->style == BLENDED)
		surface = TTF_RenderText_Blended(this->font, this->text.c_str(), this->color);

	this->texture = SDL_CreateTextureFromSurface(Window::GetRenderer(), surface);
	SDL_QueryTexture(this->texture, nullptr, nullptr, &surface->w, &surface->h);

    this->box.w = surface->w;
    this->box.h = surface->h;

	SDL_FreeSurface(surface);
}

int Text::GetWidth(){
    return box.w;
}

int Text::GetX(){
    return box.x;
}

int Text::GetY(){
    return box.y;
}

string Text::GetText(){
    return text;
}


bool Text::IsMouseInside(){
    if(box.x <= InputHandler::GetMousePosition().x && InputHandler::GetMousePosition().x <= box.x + box.w &&
       box.y <= InputHandler::GetMousePosition().y && InputHandler::GetMousePosition().y <= box.y + box.h){
        return true;
    }else return false;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

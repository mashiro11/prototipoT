#include "Relacao.h"

Relacao::Relacao(Aglutinado& aglut1, Aglutinado& aglut2, int forca):
    aglut1(aglut1),
    aglut2(aglut2),
    forca(forca)
{
    pt.x = (aglut1.GetFixedCenter().x + aglut2.GetFixedCenter().x)/2;
    pt.y = (aglut1.GetFixedCenter().y + aglut2.GetFixedCenter().y)/2;
}

Relacao::~Relacao()
{
    //dtor
}
void Relacao::AddTermo(string termo){
    termos.push_back(new Text("fonts/Roboto-Regular.ttf", 10, BLENDED, termo, 0, 0, 0xE5, 0xE5, 0xE5, SDL_ALPHA_OPAQUE));
    if(termos.size() == 1){
        termos.back()->SetPos(pt.x, pt.y);
    }else if(termos.size() > 1){
        termos.back()->SetPos(pt.x, pt.y + (termos.size()-1)*termos.back()->GetHeight());
    }
}

void Relacao::PrintTermos(){
    for(int i = 0; i < termos.size(); i++){
        cout << termos[i]->GetText() << endl;
    }
}

void Relacao::Render(){
    for(int i = 0; i < termos.size(); i++){
        termos[i]->Render();
    }
}

#include "Camera.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
#endif //DEBUG


Point Camera::position(0,0);
Point Camera::pastPosition(0,0);
Point Camera::follow(0,0);
int Camera::speed(3);
int Camera::speedMouseRoll(10);
int Camera::followSpeed(10);
bool Camera::following(false);
bool Camera::cameraScroll(true);
int Camera::windowHeight(WINDOW_HEIGHT);
int Camera::windowWidth(WINDOW_WIDTH);
Point Camera::upperBound(BOUNDARY, BOUNDARY);
Point Camera::lowerBound(WINDOW_WIDTH - BOUNDARY, WINDOW_HEIGHT - BOUNDARY);
bool Camera::cameraMove(false);

Camera::~Camera()
{
    //dtor
}

void Camera::Update(float dt){
    //Movimentação por scroll
//    if(InputHandler::GetMouseScrollX() || InputHandler::GetMouseScrollY()){
//        cameraScrolling = true;
//    }else{
//        cameraScrolling = false;
//    }

    if(cameraScroll){
        position.y += -InputHandler::GetMouseScrollY()*speedMouseRoll;
        position.x += InputHandler::GetMouseScrollX()*speedMouseRoll;
        if(position.y < -(BG_HEIGHT - WINDOW_HEIGHT)/2) position.y = -(BG_HEIGHT - WINDOW_HEIGHT)/2;
        if(position.x < -(BG_WIDTH - WINDOW_WIDTH)/2) position.x = -(BG_WIDTH - WINDOW_WIDTH)/2;
        if(position.y > BG_HEIGHT/2 -WINDOW_HEIGHT/2) position.y = BG_HEIGHT/2 -WINDOW_HEIGHT/2;
        if(position.x > BG_WIDTH/2 -WINDOW_WIDTH/2) position.x = BG_WIDTH/2 -WINDOW_WIDTH/2;
    }

    //Movimentação pelas setas
    if(InputHandler::GetKey() == SDLK_LEFT){
        position.x -= speed;
    }
    if(InputHandler::GetKey() == SDLK_UP){
        position.y -= speed;
    }
    if(InputHandler::GetKey() == SDLK_RIGHT){
        position.x += speed;
    }
    if(InputHandler::GetKey() == SDLK_DOWN){
        position.y += speed;
    }

    //Movimentação com mouse nas bordas
//    upperBound.x = position.x + BOUNDARY;
//    upperBound.y = position.y + BOUNDARY;
//
//    lowerBound.x = position.x + WINDOW_WIDTH - BOUNDARY;
//    lowerBound.y = position.y + windowHeight - BOUNDARY;
//
//    if(InputHandler::GetMouseX() + position.x < upperBound.x ){
//        position.x -= speed;
//    }else if(InputHandler::GetMouseX() + position.x > lowerBound.x ){
//        position.x += speed;
//    }
//
//    if(InputHandler::GetMouseY() + position.y < upperBound.y ){
//        position.y -= speed;
//    }else if(InputHandler::GetMouseY() + position.y > lowerBound.y ){
//        position.y += speed;
//    }

    //Movimentação por follow
    if(following){
        Point endPoint(0,0);//windowWidth/4, windowHeight/4);

        if(follow.x != position.x ||
           follow.y != position.y ){
            if(follow.x > position.x + endPoint.x){
                if( position.x + endPoint.x + followSpeed > follow.x){
                    position.x = follow.x - endPoint.x;
                }else{
                    position.x += followSpeed;
                }
            }else{
                if( position.x + endPoint.x - followSpeed < follow.x){
                    position.x = follow.x - endPoint.x;
                }else{
                    position.x -= followSpeed;
                }
            }

            if(follow.y > position.y + endPoint.y){
                if( position.y + endPoint.y + followSpeed > follow.y){
                    position.y = follow.y - endPoint.y;
                }else{
                    position.y += followSpeed;
                }
            }else{
                if( position.y + endPoint.y - followSpeed < follow.y){
                    position.y = follow.y - endPoint.y;
                }else{
                    position.y -= followSpeed;
                }
            }
        }else{
            following = false;
        }
    }
    if(pastPosition.x != position.x ||
       pastPosition.y != position.y){
        pastPosition.x = position.x;
        pastPosition.y = position.y;
        cameraMove = true;
    }else{
        cameraMove = false;
    }
}

void Camera::Follow(Point& pt){
    following = true;
    follow.x = pt.x;
    follow.y = pt.y;
    DEBUG_PRINT("Camera em " << position.x << "x" << position.y);
    DEBUG_PRINT("Seguindo o ponto " << follow.x << "x" << follow.y);
}

Point& Camera::GetFollow(){
    return follow;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG

#ifndef CAMERA_H
#define CAMERA_H

#include "InputHandler.h"
#include "Point.h"

#include "WindowSize.h"

#define BG_WIDTH    2048
#define BG_HEIGHT   1372

#define BOUNDARY 10

class Camera
{
    public:
        virtual ~Camera();
        static void Update(float dt);
        static void Follow(Point& pt);
        static Point& GetFollow();

        static Point position;
        static int speed;
        static bool cameraScroll;
        static bool cameraMove;

    protected:
    private:
        static Point pastPosition;
        static int speedMouseRoll;
        static Point follow;
        static bool following;
        static int followSpeed;
        static int windowWidth;
        static int windowHeight;
        static Point upperBound;
        static Point lowerBound;

};

#endif // CAMERA_H

#ifndef CAMERA_H
#define CAMERA_H

#include "InputHandler.h"
#include "Point.h"

#include "WindowSize.h"

#define BOUNDARY 10

class Camera
{
    public:
        virtual ~Camera();
        static void Update(float dt);
        static void Follow(Point& pt);

        static Point position;
        static int speed;
        static bool cameraScroll;

    protected:
    private:
        static int speedMouseRoll;
        static Point follow;
        static bool following;
        static int windowWidth;
        static int windowHeight;
        static Point upperBound;
        static Point lowerBound;

};

#endif // CAMERA_H

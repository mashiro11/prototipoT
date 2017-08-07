#ifndef CAMERA_H
#define CAMERA_H

#include "InputHandler.h"
#include "Point.h"

class Camera
{
    public:
        virtual ~Camera();
        static void Update(float dt);

        static Point position;
        static bool moved;

    protected:
    private:
};

#endif // CAMERA_H

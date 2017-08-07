#ifndef SCREENOBJECT_H
#define SCREENOBJECT_H

class ScreenObject
{
    public:
        virtual ~ScreenObject();
        virtual void Render() = 0;
        virtual void Update(float dt) = 0;

    protected:

    private:

};

#endif // SCREENOBJECT_H

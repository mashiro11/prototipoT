#ifndef TIMER_H
#define TIMER_H


class Timer
{
    public:
        Timer();
        //~Timer();
        void Update (float dt);
        void Restart ();
        double Get();
        void Set(double value);
        bool TimeUp();
    protected:
        /* vazio */
    private:
        double time;
        double currTime;
        bool timeUp;

};
#endif // TIMER_H

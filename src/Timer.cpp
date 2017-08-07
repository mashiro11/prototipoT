#include "../include/Timer.h"

Timer::Timer()
{
    time = currTime = 0;
    timeUp = false;
}

void Timer::Update (float dt)
{
    if(!timeUp) currTime -= dt;
    if(currTime < 0) timeUp = true;
}

void Timer::Restart ()
{
    currTime = time;
    timeUp = false;
}

double Timer::Get()
{
    return currTime;
}

void Timer::Set(double value)
{
    this->time = value;
}

bool Timer::TimeUp(){
    return timeUp;
}


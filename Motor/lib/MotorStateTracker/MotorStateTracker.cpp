#include "MotorStateTracker.h"

void MotorStateTracker::setFrame0(Frame0 new_frame)
{
    frame0=new_frame;
}

void MotorStateTracker::setFrame1(Frame1 new_frame)
{
    frame1=new_frame;
}

void MotorStateTracker::setFrame2(Frame2 new_frame)
{   frame2=new_frame;

}

Frame0 getFrame0(void)
{
    return frame0;
}

Frame1 getFrame1(void)
{
    return frame1;
}

Frame2 getFrame2(void)
{
    return frame2;
}
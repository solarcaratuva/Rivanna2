#ifndef MOTOR_STATE_TRACKER_H
#define MOTOR_STATE_TRACKER_H

#include <mbed.h>
#include "MotorControllerCANStructs.h"

class MotorStateTracker 
{
    public:
        void setFrame0(Frame0 new_frame);
        void setFrame1(Frame1 new_frame);
        void setFrame2(Frame2 new_frame);
        
        Frame0 getFrame0(void);
        Frame1 getFrame1(void);
        Frame2 getFrame2(void);

    private:
        Frame0 frame0;
        Frame1 frame1;
        Frame2 frame2;

};


#endif
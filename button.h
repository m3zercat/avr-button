/*
 * Button. Yay
 */
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <Arduino.h>

class Button {
    private:
        unsigned long nextMillis = 0;
        bool state = false;
        int pin = 23;
        int gap = 3000;
        int duration = 50;
    
    public:
        Button(int _pin);
        Button(int _pin, int _gap, int _duration);
        void SetGap(int _gap);
        void SetDuration(int _duration);
        void SetPin(int _pin);
        void Pulse();
};

#endif
/*********************************************************************************************************
 * END FILE
 *********************************************************************************************************/

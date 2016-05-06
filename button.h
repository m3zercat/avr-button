/*
 * Button. Yay
 */
#ifndef _BUTTON_H_
#define _BUTTON_H_
#define BUTTON_PRESS 0x1
#define BUTTON_HOLD 0x0

#ifndef BUTTON_MAX_PRESSES
#define BUTTON_MAX_PRESSES 5
#endif

#ifndef BUTTON_MAX_HOLDS
#define BUTTON_MAX_HOLDS 2
#endif

#include <Arduino.h>

typedef void(*FunctionPointer)();

class Button {
    private:
        uint8_t pin = 23;
        bool onStateHigh = false;
        int multiplePressMaxGap = 500;
        int deBounceDuration = 50;
        int holdDuration = 2000;
        FunctionPointer clickFunctions[BUTTON_MAX_PRESSES];
        FunctionPointer holdFunctions[BUTTON_MAX_HOLDS];

        unsigned long lastStateOnChangeMillis = 0;
        unsigned long lastStateOffChangeMillis = 0;
        
        bool state = false;

        unsigned long lastClickEndedMillis = 0;
        uint8_t clickCount = 0;
    
        unsigned long lastHoldEndedMillis = 0;
        uint8_t holdCount = 0;

        void Init(uint8_t _pin, bool _onStateHigh);

    public:
        Button(uint8_t _pin, bool _onStateHigh);
        Button(uint8_t _pin, bool _onStateHigh, int _multiplePressMaxGap, int _deBounceDuration);
        void Setup();
        void SetGap(int _multiplePressMaxGap);
        void SetDuration(int _deBounceDuration);
        void SetClickAction(uint8_t _count, FunctionPointer _function);
        void SetHoldAction(uint8_t _count, FunctionPointer _function);
        void Pulse();
};

#endif
/*********************************************************************************************************
 * END FILE
 *********************************************************************************************************/

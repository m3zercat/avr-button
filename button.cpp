/*
 * Button. Yay
 */
#include "button.h"


void NoOp(){}

/*********************************************************************************************************
 ** Function name:           ...
 ** Descriptions:            ...
 *********************************************************************************************************/
void Button::Init(uint8_t _pin, bool _onStateHigh)
{
    this->pin = _pin;
    this->onStateHigh = _onStateHigh;
    // initialize all click functions to no operation
    for(int i = 0; i < BUTTON_MAX_PRESSES; i++){
        this->clickFunctions[i] = NoOp;
    }
    // initialize all hold functions to no operation
    for(int i = 0; i < BUTTON_MAX_HOLDS; i++){
        this->holdFunctions[i] = NoOp;
    }
}

/*********************************************************************************************************
 ** Function name:           ...
 ** Descriptions:            ...
 *********************************************************************************************************/
Button::Button(uint8_t _pin, bool _onStateHigh)
{
    this->Init(_pin, _onStateHigh);
}

/*********************************************************************************************************
 ** Function name:           ...
 ** Descriptions:            ...
 *********************************************************************************************************/
Button::Button(uint8_t _pin, bool _onStateHigh, int _multiplePressMaxGap, int _deBounceDuration)
{
    this->Init(_pin, _onStateHigh);
    this->SetGap(_multiplePressMaxGap);
    this->SetDuration(_deBounceDuration);
}

/*********************************************************************************************************
 ** Function name:           ...
 ** Descriptions:            ...
 *********************************************************************************************************/
void Button::Setup()
{
    pinMode(this->pin, this->onStateHigh ? INPUT : INPUT_PULLUP);
}

/*********************************************************************************************************
 ** Function name:           ...
 ** Descriptions:            ...
 *********************************************************************************************************/
void Button::SetGap(int _multiplePressMaxGap)
{
    this->multiplePressMaxGap = _multiplePressMaxGap;
}

/*********************************************************************************************************
 ** Function name:           ...
 ** Descriptions:            ...
 *********************************************************************************************************/
void Button::SetDuration(int _deBounceDuration)
{
    this->deBounceDuration = _deBounceDuration;
}

/*********************************************************************************************************
 ** Function name:           ...
 ** Descriptions:            ...
 *********************************************************************************************************/
void Button::SetClickAction(uint8_t _count, FunctionPointer _function)
{
    this->clickFunctions[_count-1] = _function;
}

/*********************************************************************************************************
 ** Function name:           ...
 ** Descriptions:            ...
 *********************************************************************************************************/
void Button::SetHoldAction(uint8_t _count, FunctionPointer _function)
{
    this->holdFunctions[_count-1] = _function;
}

/*********************************************************************************************************
 ** Function name:           ...
 ** Descriptions:            ...
 *********************************************************************************************************/
void Button::Pulse()
{
    bool currentState = digitalRead(this->pin) == this->onStateHigh ? HIGH : LOW;

    if(currentState != this->state)
    { // the state has changed
        this->state = currentState;
        if(currentState)
        { // the state is on
            this->lastStateOnChangeMillis = millis();
        }
        else
        { // the state is off
            this->lastStateOffChangeMillis = millis();
        }

        if(this->lastStateOffChangeMillis > this->lastStateOnChangeMillis)
        { // off happenned after on
            unsigned long pressDuration = this->lastStateOffChangeMillis - this->lastStateOnChangeMillis;
            if(pressDuration > this->deBounceDuration)
            { // the press was long enough to count for something
                if(pressDuration < this->holdDuration)
                { // the press is a click
                    this->clickCount++;
                    this->lastClickEndedMillis = this->lastStateOffChangeMillis;
                }
                else
                { // the press is a hold
                    this->holdCount++;
                    this->lastHoldEndedMillis = this->lastStateOffChangeMillis;
                }
            }
        }
    }

    if(this->clickCount > 0 && (this->lastClickEndedMillis + this->multiplePressMaxGap)<millis())
    { // we have pending clicks and there can be no more
        if(this->clickCount > BUTTON_MAX_PRESSES)
        { // we have pressed more times than there are functions
            this->clickCount = BUTTON_MAX_PRESSES;
        }
        this->clickFunctions[this->clickCount-1]();
        this->clickCount = 0;
    }

    if(this->holdCount > 0 && (this->lastHoldEndedMillis + this->multiplePressMaxGap)<millis())
    { // we have pending holds and there can be no more
        if(this->holdCount > BUTTON_MAX_HOLDS)
        { // we have pressed more times than there are functions
            this->holdCount = BUTTON_MAX_HOLDS;
        }
        this->holdFunctions[this->holdCount-1]();
        this->holdCount = 0;
    }

}

/*********************************************************************************************************
 * END FILE
 *********************************************************************************************************/
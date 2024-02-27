#include "chatmc_key.hpp"
#include "Arduino.h"

namespace chatmc
{

StrtKey::StrtKey(void (*pOnActive)(), void (pOnRelease)(), int pKeyPin)
{
    onActive = pOnActive;
    onRelease = pOnRelease;
    keyPin = pKeyPin;
}

StrtKey::StrtKey(void (*pOnActive)(), void (pOnRelease)(), int pKeyPin, uint8_t pWpm)
{
    onActive = pOnActive;
    onRelease = pOnRelease;
    keyPin = pKeyPin;
    wpm =pWpm;
}


Symbol StrtKey::getSymbol()
{
    if(digitalRead(keyPin) == LOW)
    {
        if(onActive != nullptr)
        {
            onActive();
        }
        if(pressedTime == 0)
        {
            pressedTime = millis();
        }
        releasedTime = 0;
        releasedDuration = 0;
    }
    else
    {
        if(onRelease != nullptr)
        {
            onRelease();
        }
        if(releasedTime == 0)
        {
            releasedTime = millis();
        }
        else
        {
            releasedDuration = millis() - releasedTime;
        }
        if(pressedTime != 0)
        {
            pressedDuration = millis() - pressedTime;
            if(debounce < pressedDuration && pressedDuration < wpmToDah(wpm))
            {
                return Symbol::Dit;
            }
            else
            {
                return Symbol::Dah;
            }
            pressedTime = 0;
            pressedDuration = 0;
        }
    }
    return Symbol::None;
}

unsigned long StrtKey::getPressedDuration()
{
    return pressedDuration;
}

unsigned long StrtKey::getReleaseDuration()
{
    return releasedDuration;
}

IambicKey::IambicKey(void (*pOnActive)(), void (pOnRelease)(), int pDitPin, int pDahPin)
{
    onActive = pOnActive;
    onRelease = pOnRelease;
    ditPin = pDitPin;
    dahPin = pDahPin;
}

IambicKey::IambicKey(void (*pOnActive)(), void (pOnRelease)(), int pDitPin, int pDahPin, uint8_t pWpm)
{
    onActive = pOnActive;
    onRelease = pOnRelease;
    ditPin = pDitPin;
    dahPin = pDahPin;
    wpm = pWpm;
}


void IambicKey::sendElement(unsigned long duration)
{
    onActive();
    sendDuration = duration;
    sendTime = millis();
    sending = true;
}

Symbol IambicKey::getSymbol()
{
    bool isDit = digitalRead(ditPin) == LOW;
    bool isDah = digitalRead(dahPin) == LOW;
    Symbol sym = Symbol::None;
    if(!sending)
    {
        if(isDit && !isDah)
        {
            sendElement(wpmToDit(wpm));
            sym = Symbol::Dit;
        }
        else if(!isDit && isDah)
        {
            sendElement(wpmToDah(wpm));
            sym = Symbol::Dah;
        }
        else if(isDit && isDah)
        {
            if(ditState && !dahState)
            {
                sendElement(wpmToDah(wpm));
                sym = Symbol::Dah;
            }
            else if(!ditState && dahState)
            {
                sendElement(wpmToDit(wpm));
                sym = Symbol::Dit;
            }
            else
            {
                sendElement(wpmToDit(wpm));
                sym = Symbol::Dit;
            }
        }
    }
    else
    {
        if(millis() - sendTime >= sendDuration)
        {
            onRelease();
            sending = false;
            if(isDit && isDah)
            {
                if(sendDuration == wpmToDit(wpm))
                {
                    sendElement(wpmToDah(wpm));
                    sym = Symbol::Dah;
                }
                else
                {
                    sendElement(wpmToDit(wpm));
                    sym = Symbol::Dit;
                }
            }
        }
    }
    ditState = isDit;
    dahState = isDah;
    return sym;
}

}
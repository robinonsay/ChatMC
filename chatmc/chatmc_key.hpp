#ifndef CHATMC_KEY_HPP
#define CHATMC_KEY_HPP

namespace chatmc
{

constexpr unsigned int wpmToDit(uint8_t wpm)
{
    return 1200 / wpm;
}

constexpr unsigned int wpmToDah(uint8_t wpm)
{
    return wpmToDit(wpm) * 3;
}

constexpr unsigned int wpmToSymSpc(uint8_t wpm)
{
    return wpmToDit(wpm);
}

constexpr unsigned int wpmToChrSpc(uint8_t wpm)
{
    return wpmToDit(wpm) * 3;
}

constexpr unsigned int wpmToWrdSpc(uint8_t wpm)
{
    return wpmToDit(wpm) * 7;
}

enum class Symbol: char
{
    None = 0,
    Dit = '.',
    Dah = '-'
};

class StrtKey
{
    void (*onActive)() = nullptr;
    void (*onRelease)() = nullptr;
    int keyPin = 0;
    uint8_t wpm = 15;
    uint16_t debounce = 10;
    unsigned long pressedTime = 0;
    unsigned long releasedTime = 0;
    unsigned long pressedDuration = 0;
    unsigned long releasedDuration = 0;
public:
    StrtKey(void (*pOnActive)(), void (pOnRelease)(), int pKeyPin);
    StrtKey(void (*pOnActive)(), void (pOnRelease)(), int pKeyPin, uint8_t wpm);
    Symbol getSymbol();
    unsigned long getPressedDuration();
    unsigned long getReleaseDuration();
};

class IambicKey
{
    void (*onActive)() = nullptr;
    void (*onRelease)() = nullptr;
    int ditPin = 0;
    int dahPin = 0;
    uint8_t wpm = 15;
    uint16_t debounce = 10;
    bool ditState = false;
    bool dahState = false;
    bool sending = false;
    unsigned long sendTime = 0;
    unsigned long sendDuration = 0;
    void sendElement(unsigned long duration);
public:
    IambicKey(void (*pOnActive)(), void (pOnRelease)(), int pDitPin, int pDahPin);
    IambicKey(void (*pOnActive)(), void (pOnRelease)(), int pDitPin, int pDahPin, uint8_t wpm);
    Symbol getSymbol();
};

}

#endif

#ifndef CHATMC_KEYER_HPP
#define CHATMC_KEYER_HPP

#include <chrono>
#include "chatmc_sym.hpp"

using namespace std::chrono_literals;
using std::chrono::milliseconds;

namespace chatmc
{

constexpr uint16_t DEFUALT_WPM = 15;
constexpr milliseconds DEFAULT_DEBOUNCE = 2ms;
constexpr size_t MAX_BUFFER = 0x8000;

struct KeyerAPI
{
    void (*onActive)() = nullptr;
    void (*onRelease)() = nullptr;
    virtual Symbol getSymbol() = 0;
    virtual ~KeyerAPI() = default;
protected:
    KeyerAPI(void (*pOnActive)(), void (*pOnRelease)()):onActive(pOnActive), onRelease(pOnRelease)
    {};
};

template<typename Gpio>
struct IambicKeyer: KeyerAPI
{
    Gpio &ditPin;
    Gpio &dahPin;
    uint16_t wpm = DEFUALT_WPM;
    milliseconds debounce = DEFAULT_DEBOUNCE;
    IambicKeyer(
        void (*pOnActive)(),
        void (*pOnRelease)(),
        Gpio &pDitPin,
        Gpio &pDahPin
    ):KeyerAPI{pOnActive, pOnRelease}, ditPin{pDahPin}, dahPin{pDahPin}
    {}
    Symbol getSymbol();
};

}

#endif /* CHATMC_KEYER_HPP */
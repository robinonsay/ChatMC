#ifndef CHATMC_SYM_HPP
#define CHATMC_SYM_HPP
#include <cstdint>
#include <string>

namespace chatmc
{

constexpr uint8_t MAX_SYMS = 0b1000;

constexpr unsigned int wpmToDit(unsigned int wpm)
{
    return 1200 / wpm;
}

constexpr unsigned int wpmToDah(unsigned int wpm)
{
    return wpmToDit(wpm) * 3;
}

constexpr unsigned int wpmToSym(unsigned int wpm)
{
    return wpmToDit(wpm);
}

constexpr unsigned int wpmToChr(unsigned int wpm)
{
    return wpmToDit(wpm) * 3;
}

constexpr unsigned int wpmToWrd(unsigned int wpm)
{
    return wpmToDit(wpm) * 7;
}

enum class Symbol: char
{
    None = 0,
    Dit = '.',
    Dah = '-'
};

struct MorsePair {
  char code[MAX_SYMS];
  char character;
};

// Create the look-up table with Morse code and their corresponding characters
extern MorsePair morseMap[];

}

#endif /* CHATMC_SYM_HPP */

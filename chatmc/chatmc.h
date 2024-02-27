#ifndef CHATMC_HPP
#define CHATMC_HPP

#include "chatmc_key.hpp"
#include "Arduino.h"

namespace chatmc
{

struct MorseCodeMap {
  String code;
  char character;
};

// Create the look-up table with Morse code and their corresponding characters
MorseCodeMap morseCodeTable[] = {
  {".-", 'A'},
  {"-...", 'B'},
  {"-.-.", 'C'},
  {"-..", 'D'},
  {".", 'E'},
  {"..-.", 'F'},
  {"--.", 'G'},
  {"....", 'H'},
  {"..", 'I'},
  {".---", 'J'},
  {"-.-", 'K'},
  {".-..", 'L'},
  {"--", 'M'},
  {"-.", 'N'},
  {"---", 'O'},
  {".--.", 'P'},
  {"--.-", 'Q'},
  {".-.", 'R'},
  {"...", 'S'},
  {"-", 'T'},
  {"..-", 'U'},
  {"...-", 'V'},
  {".--", 'W'},
  {"-..-", 'X'},
  {"-.--", 'Y'},
  {"--..", 'Z'},
  {"-----", '0'},
  {".----", '1'},
  {"..---", '2'},
  {"...--", '3'},
  {"....-", '4'},
  {".....", '5'},
  {"-....", '6'},
  {"--...", '7'},
  {"---..", '8'},
  {"----.", '9'},
  {".-.-.-", '.'},
  {"--..--", ','},
  {"..--..", '?'},
  {"-.-.--", '!'},
  {"-..-.", '/'},
  {"-.--.", '('},
  {"-.--.-", ')'},
  {".----.", '\''},
  {"-....-", '-'},
  {"---...", ':'},
  {"-.-.-.", ';'},
  {"-...-", '='},
  {".-.-.", '+'},
  {"-..-.", '/'},
  {".--.-.", '@'}
};

char morseToChar(String &code)
{
    for(size_t i = 0; i < code.length(); i++)
    {
        if(code == morseCodeTable[i].code)
        {
            return morseCodeTable[i].character;
        }
    }
    return 0;
}

template<typename Keyer>
class ChatMc
{
    Keyer &keyer;
    String currWord = {};
    String symbols = {};
    uint8_t wpm = 15;
    unsigned long symTime = 0;
    unsigned long chrTime = 0;
public:
    ChatMc(Keyer &pKeyer)
    {
        keyer = pKeyer;
    }
    ChatMc(Keyer &pKeyer, uint8_t pWpm)
    {
        keyer = pKeyer;
        wpm = pWpm;
    }
    bool wordReady()
    {
        return millis() - symTime > wpmToWrdSpc(wpm) && symTime != 0;
    }
    String getWord()
    {
        return currWord;
    }
    void update()
    {
        Symbol symbol = keyer.getSymbol();
        if(symbol != Symbol::None)
        {
            symTime = millis();
            symbols += symbol;
        }
        if(millis() - symTime > wpmToChrSpc(wpm) && symTime != 0)
        {
            currWord += morseToChar(symbols);
        }
    }
};

}

#endif

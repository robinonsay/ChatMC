#include <iostream>
#include <mraa.hpp>
#include <chrono>
#include "chatmc.hpp"

constexpr uint8_t GPIO66 = 7;

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

steady_clock::time_point transTime;
bool keyState = false;
int count = 0;

void keyISR(void* args)
{
    mraa::Gpio *key = reinterpret_cast<mraa::Gpio*>(args);
    auto durr = duration_cast<milliseconds>(steady_clock::now() -  transTime);
    if(durr < chatmc::DEBOUNCE)
    {
        return;
    }
    bool currentState = !key->read();
    if(currentState != keyState)
    {
        if(currentState)
        {
            std::cout << "Pressed: " << count << "\n";
            count++;
        }
        keyState = currentState;
        transTime = steady_clock::now();
    }
}

int main(int argc, char const *argv[])
{
    transTime = steady_clock::now();
    mraa::Result status;
    mraa::Gpio key{GPIO66};
    status = key.dir(mraa::DIR_IN);
    if(status != mraa::SUCCESS)
    {
        std::cerr << "Error setting direction\n";
        mraa::printError(status);
        return 1;
    }
    status = key.isr(mraa::EDGE_BOTH, &keyISR, &key);
    if(status != mraa::SUCCESS)
    {
        std::cerr << "Error setting isr\n";
        mraa::printError(status);
        return 1;
    }
    pause();
    return 0;
}

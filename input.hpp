#ifndef INPUT_HPP
#define INPUT_HPP

#include <cstdint>
class Input
{
public:
    int keys[17] = {0};
    Input();
    void handleInput(bool &quit, uint8_t *r);
    bool isPressed(uint8_t key);
};

#endif // INPUT_HPP

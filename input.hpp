#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL2/SDL.h>
#include <vector>
class Input
{
public:
    // std::vector<int> keys;
    Input(SDL_Window *window, int *keys);
    void handleInput(bool &quit, int *keys, uint8_t *r);
    bool isPressed(uint8_t key, int *keys);
    SDL_Window *window;
};

#endif // INPUT_HPP

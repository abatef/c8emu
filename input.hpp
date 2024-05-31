#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL2/SDL.h>

class Input
{
public:
    Input(SDL_Window *window);
    void        handleInput(bool &quit);
    SDL_Window *window;
};

#endif // INPUT_HPP

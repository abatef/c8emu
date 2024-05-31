#include "input.hpp"

Input::Input(SDL_Window *_window)
    : window(_window)
{}

void Input::handleInput(bool &quit)
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
    }
}

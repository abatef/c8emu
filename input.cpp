#include "input.hpp"

Input::Input(SDL_Window *_window, int *k)
    : window(_window)
{
    SDL_Init(SDL_INIT_EVENTS);
}

void Input::handleInput(bool &quit, int *keys, uint8_t *r = nullptr)
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_KEYDOWN) {
            int key = 0;
            switch (e.key.keysym.sym) {
                case SDLK_KP_1 :
                    keys[1] = 1;
                    key = 1;
                    break;
                case SDLK_KP_2 :
                    keys[2] = 1;
                    key = 2;
                    break;
                case SDLK_KP_3 :
                    keys[3] = 1;
                    key = 3;
                    break;
                case SDLK_KP_4 :
                    keys[4] = 1;
                    key = 4;
                    break;
                case SDLK_KP_5 :
                    keys[5] = 1;
                    key = 5;
                    break;
                case SDLK_KP_6 :
                    keys[6] = 1;
                    key = 6;
                    break;
                case SDLK_KP_7 :
                    keys[7] = 1;
                    key = 7;
                    break;
                case SDLK_KP_8 :
                    keys[8] = 1;
                    key = 8;
                    break;
                case SDLK_KP_9 :
                    keys[9] = 1;
                    key = 9;
                    break;
                case SDLK_KP_0 :
                    keys[0] = 1;
                    key = 0;
                    break;
                case SDLK_a :
                    keys[10] = 1;
                    key = 10;
                    break;
                case SDLK_b :
                    keys[11] = 1;
                    key = 11;
                    break;
                case SDLK_c :
                    keys[12] = 1;
                    key = 12;
                    break;
                case SDLK_d :
                    keys[13] = 1;
                    key = 13;
                    break;
                case SDLK_e :
                    keys[14] = 1;
                    key = 14;
                    break;
                case SDLK_f :
                    keys[15] = 1;
                    key = 15;
                    break;
            }
            if (r != nullptr) {
                *r = key;
                quit = true;
            }
        } else if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                case SDLK_KP_1 :
                    keys[1] = 0;
                    break;
                case SDLK_KP_2 :
                    keys[2] = 0;
                    break;
                case SDLK_KP_3 :
                    keys[3] = 0;
                    break;
                case SDLK_KP_4 :
                    keys[4] = 0;
                    break;
                case SDLK_KP_5 :
                    keys[5] = 0;
                    break;
                case SDLK_KP_6 :
                    keys[6] = 0;
                    break;
                case SDLK_KP_7 :
                    keys[7] = 0;
                    break;
                case SDLK_KP_8 :
                    keys[8] = 0;
                    break;
                case SDLK_KP_9 :
                    keys[9] = 0;
                    break;
                case SDLK_KP_0 :
                    keys[0] = 0;
                    break;
                case SDLK_a :
                    keys[10] = 0;
                    break;
                case SDLK_b :
                    keys[11] = 0;
                    break;
                case SDLK_c :
                    keys[12] = 0;
                    break;
                case SDLK_d :
                    keys[13] = 0;
                    break;
                case SDLK_e :
                    keys[14] = 0;
                    break;
                case SDLK_f :
                    keys[15] = 0;
                    break;
            }
        }
    }
}

bool Input::isPressed(uint8_t key, int *keys)
{
    return keys[key];
}

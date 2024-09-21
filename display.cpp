#include "display.hpp"

#include <stdexcept>

Display::Display(int width, int height)
    : width(width), height(height), scale(width / 64), drawFlag(0) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
    window = SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        throw std::runtime_error(SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        throw std::runtime_error(SDL_GetError());
    }
}

Display::~Display() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::clear() {
    memset(pixels, 0, sizeof(pixels));
    memset(backBuffer, 0, sizeof(backBuffer));
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Display::update() {
    for (int y = 0; y < 32; ++y) {
        for (int x = 0; x < 64; ++x) {
            uint8_t wrappedX = x % width;
            uint8_t wrappedY = y % height;
            drawPixel(wrappedX, wrappedY, backBuffer[wrappedX][wrappedY]);
        }
    }
    drawFlag = 1;
}

void Display::drawPixel(int x, int y, uint8_t on) {
    backBuffer[x][y] = on;
    SDL_Rect rect = {x * scale, y * scale, scale, scale};
    SDL_SetRenderDrawColor(renderer, on ? 255 : 0, on ? 255 : 0, on ? 255 : 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Display::render() {
    if (drawFlag) {
        memcpy(pixels, backBuffer, sizeof(pixels));
        SDL_RenderPresent(renderer);
        drawFlag = 0;
    }
}

#include <SDL2/SDL.h>

class Display {
  public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width, height, scale;
    uint8_t pixels[64][32] = {0};
    uint8_t backBuffer[64][32] = {0};
    bool drawFlag;
    Display(int width, int height);
    void clear();
    void update();
    void drawPixel(int x, int y, uint8_t on);
    void render();
    ~Display();
};
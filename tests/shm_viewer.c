#include <SDL2/SDL.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define WIDTH 320
#define HEIGHT 240

static _Bool init_app(uint32_t flags)
{
    atexit(SDL_Quit);
    if (SDL_Init(flags) < 0) {
        printf("SDL INIT failed: %s", SDL_GetError());
        return 0;
    }
    return 1;
}

static uint8_t * init_data(uint8_t * data)
{
    for(size_t i = WIDTH * HEIGHT * 3; i--; )
        data[i] = (i % 3 == 0) ? (i / 3) % WIDTH :
                  (i % 3 == 1) ? (i / 3) / WIDTH : 0;

    return data;
}

static _Bool process(uint8_t * data)
{
    for(SDL_Event event; SDL_PollEvent(&event);)
        if(event.type == SDL_QUIT) return 0;

    for(size_t i = 0; i < WIDTH * HEIGHT * 3; i += 1 + rand() % 3)
        data[i] -= rand() % 8;

    return 1;
}

static void render(SDL_Renderer *renderer, SDL_Surface *data_sf)
{
    SDL_Texture *tx = SDL_CreateTextureFromSurface(renderer, data_sf);
    SDL_RenderCopy(renderer, tx, NULL, NULL);
    SDL_RenderPresent(renderer);
}

static int SDLCALL filter(void *userdata, SDL_Event * event)
{ return event->type == SDL_QUIT; }

#define mask32(BYTE) (*(uint32_t *)(uint8_t [4]){ [BYTE] = 0xff })

int main(int argc, char * argv[])
{
    (void)argc, (void)argv;
    static uint8_t buffer[WIDTH * HEIGHT * 3];

    _Bool ok = init_app(SDL_INIT_VIDEO);
    assert(ok);

    SDL_Window *sdlWindow = SDL_CreateWindow("SDL example",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WIDTH, HEIGHT,
                                          SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(sdlWindow, -1, 0);

    SDL_Surface *data_sf = SDL_CreateRGBSurfaceFrom(
            init_data(buffer), WIDTH, HEIGHT, 24, WIDTH * 3,
            mask32(0), mask32(1), mask32(2), 0);

    SDL_SetEventFilter(filter, NULL);

    for(; process(buffer); SDL_Delay(10))
        render(renderer, data_sf);

    return 0;
}
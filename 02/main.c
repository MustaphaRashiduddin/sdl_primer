#include <SDL2/SDL.h>
typedef enum { false, true } bool;

bool init();
bool load_media();
void sdl_close();

SDL_Window *window = 0;
SDL_Surface *screen_surface = 0;
SDL_Surface *hello_world = 0;

int main(int argc, char **argv)
{
        if (!init()) {
                printf("Failed to initialize!\n");
        } else {
                if (!load_media()) {
                        printf("Failed to load media!\n");
                } else {
                        SDL_BlitSurface(hello_world, 0, screen_surface, 0);
                        SDL_UpdateWindowSurface(window);
                        SDL_Delay(2000);
                }
        }
        sdl_close();
}

bool init()
{
        bool success = true;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
                success = false;
        } else {
                window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
                if (window == 0) {
                        printf("Window could not be created!! SDL_Error: %s\n", SDL_GetError());
                        success = false;
                } else {
                        screen_surface = SDL_GetWindowSurface(window);
                }
        }
        return success;
}

bool load_media()
{
        bool success = true;
        hello_world = SDL_LoadBMP("hello_world.bmp");
        if (hello_world == 0) {
                printf("Unable to load image %s! SDL_Error: %s\n", "hello_world.bmp", SDL_GetError());
                success = false;
        }
        return success;
}

void sdl_close()
{
        SDL_FreeSurface(hello_world);
        hello_world = 0;

        SDL_DestroyWindow(window);
        window = 0;

        SDL_Quit();
}

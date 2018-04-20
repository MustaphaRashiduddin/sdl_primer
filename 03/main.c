#include <SDL2/SDL.h>
#include <stdio.h>
#include "bool.h"

bool init();
bool load_media();
void sdl_close();

SDL_Window *window = NULL;
SDL_Surface *screen_surface = NULL;
SDL_Surface *out = NULL;

/* Screen dimension constants */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char **argv)
{
        /* Start up SDL and create window */
        if (!init()) {
                printf("Failed to initialize!\n");
                return 1;
        }
        /* Load media */
        if (!load_media()) {
                printf("Failed to load media!\n");
                return 1;
        }

        /* event handler */
        SDL_Event e;

        /* while app is running */
        while (1) {
                /* handle events on queue */
                while (SDL_PollEvent(&e) != 0) {
                        /* user requests quit */
                        if (e.type == SDL_QUIT)
                                goto QUIT;
                }
                /* apply the image */
                SDL_BlitSurface(out, NULL, screen_surface, NULL);

                /* update the surface */
                SDL_UpdateWindowSurface(window);
        }

QUIT:
        sdl_close();
        return 0;
}

bool init()
{
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
                return false;
        }

        /* Create window */
        window = SDL_CreateWindow("SDL Tutorial", 
                        SDL_WINDOWPOS_UNDEFINED, 
                        SDL_WINDOWPOS_UNDEFINED, 
                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
                printf("Window could not be created! SDL_Error: %s", SDL_GetError());                
                return false;
        }

        /* Get window surface */
        screen_surface = SDL_GetWindowSurface(window);
        if (screen_surface == NULL) {
                printf("error\n");
                return false;
        }

        return true;
}

bool load_media()
{
        /* Load splash img */
        out = SDL_LoadBMP("x.bmp");

        if (out == NULL) {
                printf("Unable to load image SDL_Error: %s!" , SDL_GetError());
                return false;
        }
        return true;
}

void sdl_close()
{
        /* Deallocate surface */
        SDL_FreeSurface(out);
        out = NULL;

        /* Destroy window */
        SDL_DestroyWindow(window);
        window = NULL;

        /* Quit SDL subsystems */
        SDL_Quit();
}

#include <stdio.h>
#include <SDL2/SDL.h>
#include "bool.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

enum key_press_surfaces  
{ 
        KEY_PRESS_SURFACE_DEFAULT, 
        KEY_PRESS_SURFACE_UP, 
        KEY_PRESS_SURFACE_DOWN, 
        KEY_PRESS_SURFACE_LEFT, 
        KEY_PRESS_SURFACE_RIGHT, 
        KEY_PRESS_SURFACE_TOTAL
};

/* starts up sdl and creates window */
bool init();

/* loads media */
bool load_media();

/* frees media and shuts down sdl */
void sdl_close();

/* loads individual image */
SDL_Surface *load_surface(const char *path);

/* the window we'll be rendering to */
SDL_Window *window = NULL;

/* the surface contained by the window */
SDL_Surface *screen_surface = NULL;

/* the images that correspond to a key press */
SDL_Surface *key_press_surfaces[KEY_PRESS_SURFACE_TOTAL];

SDL_Surface *current_surface = NULL;

int main(int argc, char **argv)
{
        /* start up sdl and create window */
        if (!init()) {
                printf("failed to initialize\n");
                return 1;
        }
        /* load media */
        if (!load_media()) {
                printf("failed to load media!");
                return 1;
        }

        /* main loop flag */

        /* sdl event handler */
        SDL_Event e;

        /* set default current surface */
        current_surface = key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];

        /* while application is running */
        while (1) {
                /* handle events on queue */
                while (SDL_PollEvent(&e) != 0) {
                        /* user request quit */
                        if (e.type == SDL_QUIT)
                                goto QUIT;

                        if (e.type == SDL_KEYDOWN) {
                                /* select surfaces based on key press */
                                switch (e.key.keysym.sym) {
                                case SDLK_UP:
                                        current_surface = key_press_surfaces[KEY_PRESS_SURFACE_UP]; 
                                        break;

                                case SDLK_DOWN:
                                        current_surface = key_press_surfaces[KEY_PRESS_SURFACE_DOWN];
                                        break;

                                case SDLK_LEFT:
                                        current_surface = key_press_surfaces[KEY_PRESS_SURFACE_LEFT];
                                        break;

                                case SDLK_RIGHT:
                                        current_surface = key_press_surfaces[KEY_PRESS_SURFACE_RIGHT];
                                        break;

                                default:
                                        current_surface = key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
                                        break;
                                }
                        }
                }
                /* apply current img */
                SDL_BlitSurface(current_surface, NULL, screen_surface, NULL);

                /* update the surface */
                SDL_UpdateWindowSurface(window);
        }
QUIT:
        sdl_close();
        return 0;
}

SDL_Surface *load_surface(const char *path)
{
        /* load surface at specified path */
        SDL_Surface *loaded_surface = SDL_LoadBMP(path);
        if (loaded_surface == NULL)
                printf("Unable to load image %s! SDL_Error: %s\n", path, SDL_GetError());
        return loaded_surface;
}

bool load_media()
{
        /* load default surface */
        key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] = load_surface("press.bmp");
        if (key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
                printf("failed to load up image!\n");
                return false;
        }

        key_press_surfaces[KEY_PRESS_SURFACE_UP] = load_surface("up.bmp");
        if (key_press_surfaces[KEY_PRESS_SURFACE_UP] == NULL) {
                printf("failed to load up image!\n");
                return false;
        }

        key_press_surfaces[KEY_PRESS_SURFACE_DOWN] = load_surface("down.bmp");
        if (key_press_surfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
                printf("failed to load up image!\n");
                return false;
        }

        key_press_surfaces[KEY_PRESS_SURFACE_LEFT] = load_surface("left.bmp");
        if (key_press_surfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
                printf("failed to load up image!\n");
                return false;
        }

        key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] = load_surface("right.bmp");
        if (key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
                printf("failed to load up image!\n");
                return false;
        }

        return true;;
}

bool init()
{
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                printf("sdl couldn't initialize, sdl error: %s\n", SDL_GetError());
                return false;
        } 

        window = SDL_CreateWindow("keys", 
                        SDL_WINDOWPOS_UNDEFINED, 
                        SDL_WINDOWPOS_UNDEFINED, 
                        SCREEN_WIDTH, SCREEN_HEIGHT, 
                        SDL_WINDOW_SHOWN);

        if (window == NULL) {
                printf("window creation failed, sdl error: %s\n", SDL_GetError());
                return false;
        } 

        screen_surface = SDL_GetWindowSurface(window);
        if (screen_surface == NULL) {
                printf("framebuffer surface couldn't be returned, sdl error: %s\n", SDL_GetError());
                return false;
        }
        return true;
}

void sdl_close() { } 

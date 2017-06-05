#include "screen/Screen.hpp"
#include "graphics/Map.hpp"
#include <SDL_image.h>
#include <SDL2/SDL.h>


extern int main(int argc, char **argv) {
    Screen screen;

    CHECK_INIT_SDL(SDL_Init(SDL_INIT_VIDEO));


    SDL_Window *sdlWindow = NULL;
    sdlWindow = SDL_CreateWindow("ImpInHeaven", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                                 SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 190, 40, 156, 255);
    SDL_RenderClear(renderer);

	/*SDL_Surface *image = IMG_Load("resources/images/fox.jpg");
	if (!image)
	{
		printf("IMG_Load: %s\n", IMG_GetError());
		return 1;
	}*/

	// Draws the image on the screen:
	SDL_Rect rcDest = { 20, 20, 10, 10 };

    SDL_Surface *pSurface = NULL;
    pSurface = SDL_GetWindowSurface(sdlWindow);
    SDL_Event event;
    bool end = false;
	int color = 255;
    SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, color, 0));

    Map m(20, 20);

    if (sdlWindow) {
        while (!end) {
            while (SDL_PollEvent(&event)) {
                /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
                switch (event.type) {
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                            case SDLK_ESCAPE:
                                end = true;
                                break;
							case SDLK_a:
								color = color == 255 ? 0 : 255;
                            default:break;
                        }
                        break;

                    default:
                        break;
                }

            }

			SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, color, 0));
            SDL_RenderFillRect(renderer, &rcDest);
            SDL_RenderPresent(renderer);

            SDL_UpdateWindowSurface(sdlWindow);
        }

        SDL_DestroyWindow(sdlWindow);
    }


    SDL_Quit();

    return 0;
}
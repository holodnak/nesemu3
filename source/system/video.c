//
//  video.c
//  nesemu3
//
//  Created by James Holodnak on 9/25/15.
//  Copyright (c) 2015 James Holodnak. All rights reserved.
//

#include <SDL2/SDL.h>
#include "video.h"

SDL_Window *window = 0;
SDL_Surface *screen = 0;
int windowflags = SDL_WINDOW_FULLSCREEN;

int video_init() {

    windowflags = 0;
    window = SDL_CreateWindow("nesemu3",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,windowflags);
    
    if(window == NULL) {
        printf("error creating window\n");
        return(1);
    }
    
    screen = SDL_GetWindowSurface(window);
    if(screen == NULL) {
        video_kill();
        printf("error getting window surface\n");
        return(2);
    }

    return(0);
}

void video_kill() {
    if(window) {
        SDL_DestroyWindow(window);
    }
    window = 0;
    screen = 0;
}

void video_frameend()
{
    SDL_UpdateWindowSurface(window);
}
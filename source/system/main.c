//
//  main.c
//  nesemu3
//
//  Created by James Holodnak on 9/24/15.
//  Copyright (c) 2015 James Holodnak. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include "system/main.h"
#include "system/video.h"
#include "gui/gui.h"

int quit = 0;
int running = 0;
char configfilename[MAX_PATH];
char exepath[MAX_PATH];



int main(int argc, const char * argv[]) {
    SDL_Event event;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("SDL_Init failed\n");
        return(1);
    }

    if(video_init() != 0) {
        SDL_Quit();
        return(2);
    }
    
    gui_init();

    while(quit == 0) {
        gui_draw();
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                quit++;
            }
        }
        video_frameend();
    }
    
    gui_kill();

    video_kill();
    SDL_Quit();
    return(0);
}

//
//  gui.c
//  nesemu3
//
//  Created by James Holodnak on 9/25/15.
//  Copyright (c) 2015 James Holodnak. All rights reserved.
//

#include <SDL2_image/SDL_image.h>
#include "gui/gui.h"
#include "system/video.h"

static int flags = IMG_INIT_JPG | IMG_INIT_PNG;

int gui_init() {
    int ret;
    
    ret = IMG_Init(flags);
    if((ret & flags) != flags) {
        printf("IMG_Init failed to init required img file types\n");
        return(1);
    }
    
    return(0);
}

void gui_kill() {
    IMG_Quit();
}

SDL_Surface *gui_loadbox(char *filename) {
    SDL_Surface *ret = NULL;
    SDL_Surface *tmp = IMG_Load(filename);

    if(tmp == NULL) {
        printf("unable to load image '%s'\n",filename);
    }
    else {
        ret = SDL_ConvertSurface(tmp,screen->format,0);
        if(ret == NULL) {
            printf("unable to optimize surface of '%s'\n",filename);
        }
        SDL_FreeSurface(tmp);
    }
    return(ret);
}

void gui_draw() {
    SDL_Surface *box = gui_loadbox("box/Super Mario Bros..jpg");
    SDL_Rect rect;

    rect.x = 300;
    rect.y = 50;
    rect.w = 200;
    rect.h = 400;
    if(box != NULL) {
        SDL_BlitScaled(box,NULL,screen,&rect);
    }
}

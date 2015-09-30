//
//  video.h
//  nesemu3
//
//  Created by James Holodnak on 9/25/15.
//  Copyright (c) 2015 James Holodnak. All rights reserved.
//

#ifndef __nesemu3__video__
#define __nesemu3__video__

#include <SDL2/SDL.h>

extern SDL_Surface *screen;

int video_init();
void video_kill();
void video_framestart();
void video_frameend();

#endif /* defined(__nesemu3__video__) */

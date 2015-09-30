//
//  video.h
//  nesemu3
//
//  Created by James Holodnak on 9/25/15.
//  Copyright (c) 2015 James Holodnak. All rights reserved.
//

#ifndef __nesemu3__main__
#define __nesemu3__main__

#include <SDL2/SDL.h>

#ifndef MAX_PATH
    #define MAX_PATH	4096
#endif

#ifdef WIN32
    #define PATH_SEPERATOR  '\\'
#else
    #define PATH_SEPERATOR  '/'
#endif

#define CONFIG_FILENAME		"nesemu2.cfg"

extern int quit;
extern int running;
extern char configfilename[];
extern char exepath[];

#endif /* defined(__nesemu3__main__) */

/***************************************************************************
 *   Copyright (C) 2013 by James Holodnak                                  *
 *   jamesholodnak@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "font.h"
#include "fontdata.h"

#define TEXT_RED    0xEE
#define TEXT_GREEN  0xEE
#define TEXT_BLUE   0xEE
#define TEXTCOLOR16	((TEXT_RED << 16) | (TEXT_GREEN << 8) | (TEXT_BLUE << 0))
#define TEXTCOLOR32	((TEXT_RED << 16) | (TEXT_GREEN << 8) | (TEXT_BLUE << 0))

static int getindex(char ch)
{
	int i;

	for(i=0;fontmap[i];i++) {
		if(fontmap[i] == ch)
			return(i);
	}
	return(-1);
}

void font_drawchar32(char ch,u32 *dest,int pitch)
{
	int x,y,index = getindex(ch);
	u8 *bits = fontbits;

	if(index == -1)
		return;
	bits += index * 8;
	for(y=0;y<8;y++) {
		for(x=0;x<8;x++) {
			if(bits[y] & (1 << x))
				dest[7 - x] = TEXTCOLOR32;
		}
		dest += pitch;
	}
}

void font_drawstr32(char *str,u32 *dest,int pitch)
{
	while(*str) {
		font_drawchar32(*str++,dest,pitch);
		dest += 8;
	}
}

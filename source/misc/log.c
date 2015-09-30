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

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "misc/log.h"
#include "misc/config.h"
#include "misc/paths.h"
#include "misc/strutil.h"
#include "misc/history.h"
#include "system/main.h"
#include "version.h"

#define LOGFILENAME "nesemu2.log"

static FILE *logfd = 0;
static char logfilename[MAX_PATH] = "";
static void (*loghook)(char*) = 0;
static history_t history = {0,0};

int log_init()
{
	historyline_t *line;

	if(logfd) {
		printf("log_init:  already initialized\n");
		return(0);
	}

	//clear the string
	memset(logfilename,0,MAX_PATH);

	//parse the log path
	config_get_eval_string(logfilename,"path.user");

	//append the path seperator
	str_appendchar(logfilename,PATH_SEPERATOR);

	//append the bios filename
	strcat(logfilename,LOGFILENAME);

	//try to open
	if((logfd = fopen(logfilename,"wt")) == 0) {
		strcpy(logfilename,LOGFILENAME);
		if((logfd = fopen(LOGFILENAME,"wt")) == 0) {
			printf("log_init:  error opening log file '%s'\n",logfilename);
			return(1);
		}
	}

	//catch up the log file with lines that weren't added
	line = history.lines;
	while(line->next) {
		line = line->next;
	}
	while(line) {
		fputs(line->str,logfd);
		line = line->prev;
	}
	fflush(logfd);
	history_clear(&history);

	log_printf("log_init:  log initialized.  nesemu2 v"VERSION"\n");
	log_printf("log_init:  log filename is '%s'.\n",logfilename);
	return(0);
}

void log_kill()
{
	if(logfd)
		fclose(logfd);
	logfd = 0;
}

void log_sethook(void (*hook)(char*))
{
	loghook = hook;
}

void log_print(char *str)
{
	//output message to stdout
	printf("%s",str);

	//output message to hook function
	if(loghook) {
		loghook(str);
	}

	//if log file isnt open, maybe logging is disabled or file isnt opened yet
	if(logfd == 0) {
		history_add(&history,str);
		return;
	}

	//write to log file
	fputs(str,logfd);

	//flush file
	fflush(logfd);
}

void log_printf(char *str,...)
{
	char buffer[1024];						//buffer to store vsprintf'd message in
	va_list argptr;							//argument data

	va_start(argptr,str);					//get data
	vsprintf(buffer,str,argptr);			//print to buffer
	va_end(argptr);							//done!
	log_print(buffer);
}

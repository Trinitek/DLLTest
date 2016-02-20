
#ifndef _LOGGER_H
#define _LOGGER_H

#include <stdio.h>
#include "warnlevel.h"
#include "plugindll.h"

void writeLog(char* origin, WARNLEVEL level, char* message);
void plugin_writeLog(struct PLUGINDLL* plugin, WARNLEVEL level, char* message);
char* levelToString(WARNLEVEL level);

#endif

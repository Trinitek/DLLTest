
#ifndef _PLUGINDLL_H
#define _PLUGINDLL_H

#include <windows.h>
#include "warnlevel.h"

typedef struct PLUGINDLL {
    char* filename;
    HMODULE library;
    int (*Initialize)(struct PLUGINDLL* plugin);
    int (*PluginMain)(struct PLUGINDLL* plugin);
    int (*OnUnload)(struct PLUGINDLL* plugin);
    char* name;
    void (*writeLog)(struct PLUGINDLL* plugin, WARNLEVEL level, char* message);
} PLUGINDLL;

typedef int (*plugin_Initialize)(struct PLUGINDLL* plugin);
typedef int (*plugin_PluginMain)(struct PLUGINDLL* plugin);
typedef int (*plugin_OnUnload)(struct PLUGINDLL* plugin);

#endif


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "plugindll.h"
#include "logger.h"

int validatePlugin(PLUGINDLL* plugin) {
    int fail = 0;
    char* errString = malloc(sizeof(char) * 256);
    
    plugin->Initialize = (plugin_Initialize) GetProcAddress(plugin->library, "Initialize");
    if (plugin->Initialize == NULL) {
        snprintf(errString, 256, "Invalid plugin! Plugin '%s' has no initializer!?", plugin->filename);
        writeLog("Validate", severe, errString);
        fail = 1;
    }
    
    plugin->PluginMain = (plugin_PluginMain) GetProcAddress(plugin->library, "PluginMain");
    if (plugin->PluginMain == NULL) {
        snprintf(errString, 256, "Invalid plugin! Plugin '%s' has no main function!?", plugin->filename);
        writeLog("Validate", severe, errString);
        fail = 1;
    }
    
    plugin->OnUnload = (plugin_OnUnload) GetProcAddress(plugin->library, "OnUnload");
    if (plugin->OnUnload == NULL) {
        snprintf(errString, 256, "Invalid plugin! Plugin '%s' has no unload event handler!?", plugin->filename);
        writeLog("Validate", severe, errString);
        fail = 1;
    }
    
    if (fail == 0) {
        snprintf(errString, 256, "Plugin '%s' is valid", plugin->filename);
        writeLog("Validate", info, errString);
    }
    
    free(errString);
    return fail;
}

int loadPlugin(PLUGINDLL* plugin) {
    if (plugin->filename == NULL) {
        writeLog("Loader", severe, "The plugin filename is null");
        return 1;
    }
    
    HMODULE library = LoadLibrary(plugin->filename);
    if (library == NULL) {
        char* errString = malloc(sizeof(char) * 256);
        snprintf(errString, 256, "Could not import plugin '%s'", plugin->filename);
        writeLog("Loader", severe, errString);
        free(errString);
        return 1;
    }
    
    char* loadOk = malloc(sizeof(char) * 256);
    snprintf(loadOk, 256, "Imported plugin '%s'", plugin->filename);
    writeLog("Loader", info, loadOk);
    free(loadOk);
    
    plugin->library = library;
    plugin->writeLog = plugin_writeLog;
    
    return validatePlugin(plugin);
}

int loadPlugins(int pluginCount, PLUGINDLL** plugins) {
    for (pluginCount--; pluginCount >= 0; pluginCount--) {
        if (loadPlugin(plugins[pluginCount]) == 1) {
            plugins[pluginCount] = NULL;
        }
    }
    
    return 0;
}

int initializePlugins(int pluginCount, PLUGINDLL** plugins) {
    for (pluginCount--; pluginCount >= 0; pluginCount--) {
        if (plugins[pluginCount] != NULL) {
            plugins[pluginCount]->Initialize(plugins[pluginCount]);
        }
    }
    return 0;
}

int startPlugins(int pluginCount, PLUGINDLL** plugins) {
    for (pluginCount--; pluginCount >= 0; pluginCount--) {
        if (plugins[pluginCount] != NULL) {
            plugins[pluginCount]->PluginMain(plugins[pluginCount]);
        }
    }
    
    return 0;
}

int stopPlugins(int pluginCount, PLUGINDLL** plugins) {
    for (pluginCount--; pluginCount >= 0; pluginCount--) {
        if (plugins[pluginCount] != NULL) {
            plugins[pluginCount]->OnUnload(plugins[pluginCount]);
        }
    }
    
    return 0;
}

int main(void) {
    printf("Hello world!\n");
    
    PLUGINDLL* plugin1 = malloc(sizeof(PLUGINDLL));
    plugin1->filename = "examplePlugin.dll";
    
    int pluginCount = 1;
    PLUGINDLL* plugins[] = {
        plugin1
    };
    
    writeLog("Main", info, "Loading plugins...");
    loadPlugins(pluginCount, plugins);
    
    writeLog("Main", info, "Initializing plugins...");
    initializePlugins(pluginCount, plugins);
    
    writeLog("Main", info, "Starting plugins...");
    startPlugins(pluginCount, plugins);
    
    writeLog("Main", info, "Stopping plugins...");
    stopPlugins(pluginCount, plugins);
    
    free(plugin1);
    
    return 0;
}

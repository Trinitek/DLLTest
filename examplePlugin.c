
#include "plugindll.h"

PLUGINDLL* plugin;

int DllMain(void) {
    return 1;
}

int Initialize(PLUGINDLL* thisPlugin) {
    plugin = thisPlugin;
    plugin->name = "ExamplePlugin";
    return 0;
}

int PluginMain(void) {
    plugin->writeLog(plugin, info, "Greetings from the plugin!");
    return 0;
}

int OnUnload(void) {
    plugin->writeLog(plugin, info, "Goodnight world!");
    return 0;
}

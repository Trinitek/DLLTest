
#include "logger.h"

void writeLog(char* origin, WARNLEVEL level, char* message) {
    if (origin == NULL) {
        origin = "???";
    }
    if (message == NULL) {
        message = "";
    }
    printf("[%s] [%s] %s\n", levelToString(level), origin, message);
    return;
}

void plugin_writeLog(PLUGINDLL* plugin, WARNLEVEL level, char* message) {
    writeLog(plugin->name, level, message);
    return;
}

char* levelToString(WARNLEVEL level) {
    switch (level) {
        case debug:
            return "DEBUG";
        case info:
            return "INFO";
        case warn:
            return "WARN";
        case severe:
            return "SEVERE";
        default:
            return "???";
    }
}
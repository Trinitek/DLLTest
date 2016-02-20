gcc -shared -o examplePlugin.dll examplePlugin.c logger.c -std=c11
gcc -o main.exe main.c logger.c -std=c11

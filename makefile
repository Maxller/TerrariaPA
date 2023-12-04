all: .\src\main.cpp
	g++ .\src\main.cpp -g -IC:\msys64\mingw64\include\SDL2 -Iinclude -LC:\msys64\mingw64\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o bin\Terraria
	
dbug : all
	gdb .\bin\Terraria

run : all 
	.\bin\Terraria
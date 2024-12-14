set files=src/glad.c src\main.c
set libs=W:\lib\SDL2main.lib W:\lib\SDL2.lib W:\lib\freetype.lib

CL /Zi /I W:\includes %files% /link %libs% /OUT:mygame.exe
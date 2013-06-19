luasdl
======
A lua wrapper for SDL library

Install instructions:
====================
1. install sdl: sudo apt-get install libsdl1.2-dev
2. install sdl_ttf: sudo apt-get install libsdl-ttf2.0-dev
3. download package: git clone https://github.com/aikuharenko/luasdl.git
4. install package: sudo luarocks make luasdl-1.0-0.rockspec
5. if libluasdl could not be found then add library path: export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib/lua/5.1/
6. run example: torch example.lua



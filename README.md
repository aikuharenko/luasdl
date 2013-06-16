luasdl
======
A lua wrapper for SDL library

Install instructions:
====================
1. install sdl: sudo apt-get install libsdl1.2-dev
2. download package: git clone https://github.com/aikuharenko/luasdl.git
3. install package: sudo luarocks make luasdl-1.0-0.rockspec
4. if libluasdl could not be found then add library path: export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib/lua/5.1/

Example of usage:
================
require 'luasdl'
require 'image'

luasdl.init(512, 512)
local im = image.lena()
im = luasdl.addrect(im, 100, 100, 200, 200, 5, {1,0,0})
luasdl.display(im)



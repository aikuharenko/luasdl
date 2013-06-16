cmake_minimum_required (VERSION 2.6)

FIND_PACKAGE(Torch REQUIRED)
#name of .so lib, which will be in /lib/lua/5.1

set (libname luasdl)
set (src sdl_api.c)
set (luasrc init.lua sdl_api.h)


ADD_TORCH_PACKAGE("${libname}" "${src}" "${luasrc}" "sdl lua api")
target_link_libraries (${libname} SDL)




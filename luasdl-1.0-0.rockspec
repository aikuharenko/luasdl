package = "luasdl"
version = "1.0-0"

source = {
   url = "https://github.com/aikuharenko/luasdl.git"
}

description = {
   summary = "A lua wrapper for SDL library",
   detailed = [[
This package provides sdl api from lua 
   ]],
   homepage = "https://github.com/aikuharenko/luasdl",
   license = "BSD"
}

dependencies = {
   "torch >= 7.0",
}

build = {
   type = "cmake",
   variables = {
      LUAROCKS_PREFIX = "$(PREFIX)"
   }
}

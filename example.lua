require 'luasdl'
require 'image'

luasdl.init(512, 512, 'lena')
local im = image.lena()
im = luasdl.addrect(im, 150, 150, 250, 250, 5, {1,0,0})
luasdl.display(im)
luasdl.wait(3000)

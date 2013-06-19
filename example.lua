require 'luasdl'
require 'image'

luasdl.init(512, 512, 'lena')
local im = image.lena()
im = luasdl.addrect(im, 150, 150, 250, 250, 2, {0, 255, 0})
luasdl.display(im)
luasdl.drawtext('hi, lena', 16, 150, 130, {0, 255, 0})
luasdl.wait(3000)

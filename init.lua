require 'torch'
local ffi = require 'ffi'
require 'torchffi'
require 'image'
require 'paths'


ffi.cdef(io.open(paths.install_lua_path .. '/luasdl/sdl_api.h', 'r'):read('*a'))
ffi.cdef[[

void cdisplay(SDL_Surface *, float*, int width, int height);
SDL_Surface* init(int width, int height, const uint8_t * title);
int check_window_closed();

]]

luasdl = {}

function luasdl.init(width, height, title)

	print('init lua sdl')
	local sdl = ffi.load("luasdl")
	luasdl.sdl = sdl
	luasdl.screen = sdl.init(width, height, title)

end

function luasdl.check_window()

	t = luasdl.sdl.check_window_closed()
	return t

end

function luasdl.display(img)

	im = img:type('torch.FloatTensor'):contiguous()

	local img_c = torch.data(im)
	local width = (#im)[3]
	local height = (#im)[2]

	luasdl.sdl.cdisplay(luasdl.screen, img_c, width, height)	

end

function luasdl.addrect(im, x1, y1, w, h, r, col)

	local x2 = x1 + w -r
	local y2 = y1 + h -r
	local min = math.min
	local max = math.max
	local sx = (#im)[3]
	local sy = (#im)[2]

	for i = 1, 3 do

		im[{i, {max(1, y1 - r), min(sy, y2 + r)}, {max(1, x1 - r), min(sx, x1 + r)}}]:fill(col[i])
		im[{i, {max(1, y1 - r), min(sy, y2 + r)}, {max(1, x2 - r), min(sx, x2 + r)}}]:fill(col[i])
		im[{i, {max(1, y1 - r), min(sy, y1 + r)}, {max(1, x1), min(sx, x2) }}]:fill(col[i])
		im[{i, {max(1, y2 - r), min(sy, y2 + r)}, {max(1, x1), min(sx, x2) }}]:fill(col[i])

	end

	return im

end

function luasdl.wait(n)

	luasdl.sdl.SDL_Delay(n)

end

function luasdl.quit()

	luasdl.sdl.SDL_Quit()

end



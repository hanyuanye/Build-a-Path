#include "TextureManager.h"



TextureManager::TextureManager(SDL_Renderer* _ren, std::string path, const int & r, const int & b, const int & g, const int & _width, const int & _height)
{
	ren = _ren;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, r, b, g));
	texture = SDL_CreateTextureFromSurface(ren, loadedSurface);
	width = _width;
	height = _height;
}

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
	free();
}


void TextureManager::free()
{
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		width = 0;
		height = 0;
	}
}

void TextureManager::render(const Vec2d & pos)
{
	SDL_Rect renderQuad = { pos.get_x(), pos.get_y(), width, height };
	SDL_RenderCopy(ren, texture, NULL, &renderQuad);
	//	std::cout << SDL_GetError() << std::endl;
}

int TextureManager::get_width()
{
	return width;
}

int TextureManager::get_height()
{
	return height;
}

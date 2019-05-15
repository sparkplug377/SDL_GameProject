#include "Texture.h"


Texture::Texture() {
	// set the texture to default value (nullptr)
	m_texture = nullptr;
	// set the width and height to default value (0)
	m_width = 0;
	m_height = 0;
}

bool Texture::LoadBMPFromFile(const char* path, SDL_Renderer* renderer) {
	//	remove the old texture
	ResetTexture();

	// load image at the specified path
	if (m_texture == nullptr) {
		// load the image to the surface
		SDL_Surface* loadedSurface = SDL_LoadBMP(path);

		// if the image was successfully loaded
		if (loadedSurface != nullptr) {
			SDL_Log("Load Texture - success");

			// color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));

			// create texture from surface pixels
			m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

			// if the texture was successfully created from the loaded surface
			if (m_texture != nullptr) {
				SDL_Log("Create texture from surface - success");
				// get texture dimensions
				m_width = loadedSurface->w;
				m_height = loadedSurface->h;
			}
			else {
				SDL_Log("create texture from surface - failed %s\n", SDL_GetError());
			}

			// free the loaded surface
			SDL_FreeSurface(loadedSurface);
		}
		else {
			SDL_Log("Load Texture - failed %s\n", SDL_GetError());
		}
	}
	else {
		SDL_Log("remove the existing texture before loading a texture");
		return false;
	}
	return m_texture != nullptr;
}

bool Texture::LoadPNGFromFile(const char * path, SDL_Renderer * renderer) {
	//	remove the old texture
	ResetTexture();

	// load image at the specified path
	if (m_texture == nullptr) {
		// load the image to the surface
		SDL_Surface* loadedSurface = IMG_Load(path);

		// if the image was successfully loaded
		if (loadedSurface != nullptr) {
			SDL_Log("Load Texture - success");

			// color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 157, 142, 135));

			// create texture from surface pixels
			m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

			// if the texture was successfully created from the loaded surface
			if (m_texture != nullptr) {
				SDL_Log("Create texture from surface - success");
				// get texture dimensions
				m_width = loadedSurface->w;
				m_height = loadedSurface->h;
			}
			else {
				SDL_Log("create texture from surface - failed %s\n", SDL_GetError());
			}

			// free the loaded surface
			SDL_FreeSurface(loadedSurface);
		}
		else {
			SDL_Log("Load Texture - failed %s\n", SDL_GetError());
		}
	}
	else {
		SDL_Log("remove the existing texture before loading a texture");
		return false;
	}
	return m_texture != nullptr;
}

void Texture::Draw(SDL_Renderer* renderer, int x, int y, SDL_Rect * sourceRect) {
	// set the rendering space and render to dimensions
	SDL_Rect destRect = { x, y, m_width, m_height };

	// set clip rendering dimensions
	if (sourceRect != nullptr) {
		destRect.w = sourceRect->w;
		destRect.h = sourceRect->h;
	}

	// render to screen
	SDL_RenderCopy(renderer, m_texture, sourceRect, &destRect);
}

void Texture::DrawEx(SDL_Renderer * renderer, int x, int y, SDL_Rect * sourceRect, float angle)
{
	// set the rendering space and render to dimensions
	SDL_Rect destRect = { x, y, m_width, m_height };

	// set clip rendering dimensions
	if (sourceRect != nullptr) {
		destRect.w = sourceRect->w;
		destRect.h = sourceRect->h;
	}

	// render to screen
	SDL_RenderCopyEx(renderer, m_texture, sourceRect, &destRect, angle, NULL, SDL_FLIP_NONE);
}


void Texture::ResetTexture() {
	// deallocate the texture
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}

Texture::~Texture() {
	// deallocate
	ResetTexture();
}

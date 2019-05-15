#ifndef TEXTURE_H_
#define TEXTURE_H_

// using SDL
#include <SDL.h>
#include <SDL_image.h>

class Texture {
public:
	// allocates memory
	Texture();

	// @brief loads BMP image from the given path
	// @param path - get the path where the image is store on our computer
	// @param renderer - to create the texture from SDL_Surface
	bool LoadBMPFromFile(const char* path, SDL_Renderer* renderer);

	// @brief loads a PNG image from the given path
	// @param path - get the path where the image is store on our computer
	// @param renderer - to create the texture from SDL_Surface
	bool LoadPNGFromFile(const char* path, SDL_Renderer* renderer);

	// @brief renders texture to the screen
	// @param renderer - to copy the texture on the renderer
	// @param x,y - position of the texture on the screen
	// @param sourceRect - the area we want to copy from a texture onto the window
	void Draw(SDL_Renderer* renderer, int x, int y, SDL_Rect* sourceRect = NULL);

	// @brief renders texture to the screen with rotation
	// @param renderer - to copy the texture on the renderer
	// @param x,y - position of the texture on the screen
	// @param sourceRect - the area we want to copy from a texture onto the window
	// @param angle - rotates the texture
	void DrawEx(SDL_Renderer* renderer, int x, int y, SDL_Rect* sourceRect = NULL, float angle = 0.0f);

	// return the texture dimensions
	const int GetImageWidth() const { return m_width; }
	const int GetImageHeight() const { return m_height; }

	// remove texture from the memory
	void ResetTexture();

	// deallocates memory
	~Texture();

private:
	// hardware accelerated texture rendering
	SDL_Texture* m_texture;
	// texture dimensions
	int m_width;
	int m_height;

};

#endif
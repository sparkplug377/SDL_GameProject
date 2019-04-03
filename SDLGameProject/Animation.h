#pragma once
#include "Texture.h"
#include <vector>

class Animation {
public:
	// set default values
	Animation();

	// load texture and set the time for each frame
	Animation(Texture* spriteSheet, float frameDuration = 0.1f);

	// @brief add sprite frame
	// @param x - x position of the sprite
	// @param y - y position of the sprite
	// @param w - width of the sprite
	// @param h - height of the sprite
	void AddFrame(int x, int y, int w, int h);

	// returns the number of frames stored in the array
	const int GetFrameSize() const;

	// upates each frame
	void Update(float deltaTime);

	//draws each frame
	void Draw(SDL_Renderer* renderer, int x, int y);

	// deallocate memory
	~Animation();

private:
	// delay between each frame
	float m_frameDuration;
	// stores the sprite sheet
	Texture* m_spriteSheet;
	// timer for each frame 
	float m_frameTimer;
	// current frame in the sprite sheet
	int m_currentFrame;
	// array of frames (source Rect)
	std::vector<SDL_Rect> m_frames;
};


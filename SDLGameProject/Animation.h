#pragma once
#include "Texture.h"
#include <vector>

class Animation {
public:
	Animation();

	Animation(Texture* spriteSheet, int numberOfFrames, float frameDuration = 0.1f);

	// add sprite frame
	void AddFrame(int x, int y, int w, int h);

	// upates each frame
	void Update(float deltaTime);

	//draws each frame
	void Draw(SDL_Renderer* renderer, int x, int y);

	~Animation();

private:
	// Get the number of frames in the sprite sheet
	int m_numberOfFrames;
	// width of each frame in the sprite sheet
	int m_frameWidth;
	// height of each frame in the sprite sheet
	int m_frameHeight;
	// delay between each frame
	float m_frameDuration;
	// stores the sprite sheet
	Texture* m_spriteSheet;
	// timer for each frame 
	float m_frameTimer;
	// current frame in the sprite sheet
	int m_currentFrame;
	// array of frames
	std::vector<SDL_Rect> m_frames;
};


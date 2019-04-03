#include "Animation.h"

// reset all the variables to null
Animation::Animation() : m_frameDuration(0.0f), m_currentFrame(0), 
						m_spriteSheet(nullptr), m_frameTimer(0.0f){
}

Animation::Animation(Texture * spriteSheet, float frameDuration) {
	// load the sprite sheet
	m_spriteSheet = spriteSheet;	
	// time for each frame
	m_frameDuration = frameDuration;
	// timer
	m_frameTimer = 0.0f;
	// current frame in the sprite sheet
	m_currentFrame = 0;
}

void Animation::AddFrame(int x, int y, int w, int h) {
	// create a frame from given position and size
	SDL_Rect frame = { x, y, w, h };
	// push the frame into the array
	m_frames.push_back(frame);
}

const int Animation::GetFrameSize() const {
	return m_frames.size();
}

void Animation::Update(float deltaTime) {
	// cycle through animation frames

	// update frameTimer
	m_frameTimer += deltaTime;

	// if the current frame has reached it's duration
	if (m_frameTimer >= m_frameDuration) {
		// go to the next frame
		m_currentFrame++;
		// reset frame timer
		m_frameTimer = 0.0f;

		// if we reached the end of the spritesheet
		if (m_currentFrame >= m_frames.size()) {
			// start again from the first frame
			m_currentFrame = 0;
		}

	}
}

void Animation::Draw(SDL_Renderer * renderer, int x, int y) {
	// draw
	m_spriteSheet->Draw(renderer, x, y, &m_frames[m_currentFrame]);
}

Animation::~Animation() {
	// deallocate the sprite sheet
	if (m_spriteSheet != nullptr) {
		delete m_spriteSheet;
		m_spriteSheet = nullptr;
	}
}

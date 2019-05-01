#ifndef INPUT_H_
#define INPUT_H_

#include <SDL.h>
#include <vector>
enum MouseInput {
	MOUSE_BUTTON_LEFT	= 0,
	MOUSE_BUTTON_RIGHT	= 1,
	MOUSE_BUTTON_MIDDLE	= 2,
	MOUSE_BUTTON_4		= 3,
	MOUSE_BUTTON_5		= 4
};

class Input
{
public:
	static Input* GetInstance();

	static void Create();
	static void Destroy();

	~Input();

	void UpdateInput();

	// keyboard handling events
	bool IsKeyDown(SDL_Scancode key);
	bool IsKeyUp(SDL_Scancode key);

	// mouse handling events
	bool IsMouseDown(MouseInput button);
	bool IsMouseUp(MouseInput button);
	
	// returns the x position of mouse
	int GetMouseX();
	// returns the y position of mouse
	int GetMouseY();
	// returns the x and y position of mouse
	void GetMousePos(int* x, int *y);

private:
	Input();
	// singleton variable
	static Input* m_instance;

	// keyboard events
	void OnKeyDown();
	void OnKeyUp();
	// keyboard specifications
	const Uint8* m_keyboardState;

	// mouse specification
	int m_mouseX;
	int m_mouseY;
	std::vector<bool> m_mouseButtonStates;
	// mouse events
	void OnMouseDown(SDL_Event& e);
	void OnMouseUp(SDL_Event& e);
	void OnMouseMove(SDL_Event& e);

};

#endif

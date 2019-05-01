#ifndef INPUT_H_
#define INPUT_H_

#include <SDL.h>
#include <vector>

// list of buttons for the mouse
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
	// @brief	Input is a singleton class.
	//			returns the instance of the input class
	static Input* GetInstance();

	// @brief	creates an instance of the input class
	static void Create();
	// @brief	destroys the instance of the input class
	static void Destroy();

	~Input();

	// @brief	updates the keyboard and mouse events.
	void UpdateInput();

	// keyboard handling events
	// @brief	key pressed
	bool IsKeyDown(SDL_Scancode key);
	// @brief	key released
	bool IsKeyUp(SDL_Scancode key);

	// mouse handling events
	// @brief	mouse button pressed
	bool IsMouseDown(MouseInput button);
	// @brief	mouse button released
	bool IsMouseUp(MouseInput button);
	
	// @brief	returns the x position of mouse
	int GetMouseX();
	// @brief	returns the y position of mouse
	int GetMouseY();
	// @brief	returns the x and y position of mouse
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

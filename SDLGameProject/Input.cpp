#include "Input.h"
#include "Game.h"

Input* Input::m_instance = nullptr;

Input::Input()
{
	m_keyboardState = 0;

	// setting the button states to false by default
	for (int i = 0; i < 5; ++i) {
		m_mouseButtonStates.push_back(false);
	}

	m_mouseX = 0;
	m_mouseY = 0;
}


Input * Input::GetInstance()
{
	// return the instance of the input
	return m_instance;
}

void Input::Create()
{
	// check if there is no input
	if (m_instance == nullptr) {
		// create an input
		m_instance = new Input();
	}
}

void Input::Destroy()
{
	if (m_instance != nullptr) {
		// removes the instance of the input from the memory
		delete m_instance;
		// set the pointer to nullptr
		m_instance = nullptr;
	}
}

Input::~Input()
{
	// check if the size is greater than 0
	if (m_mouseButtonStates.size() > 0)
	{
		// remove all the items in the array
		m_mouseButtonStates.clear();
	}
}

void Input::UpdateInput()
{
	SDL_Event e;
	if (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			Game::GetInstance()->Quit();
			break;
		case SDL_KEYDOWN:
			OnKeyDown();
			break;
		case SDL_KEYUP:
			OnKeyUp();
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnMouseDown(e);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseUp(e);
			break;
		case SDL_MOUSEMOTION:
			OnMouseMove(e);
			break;
		default:
			break;
		}
	}
}

bool Input::IsKeyDown(SDL_Scancode key)
{
	if (m_keyboardState != nullptr) {
		if (m_keyboardState[key] == 1)
			return true;
	}
	return false;
}

bool Input::IsKeyUp(SDL_Scancode key)
{
	if (m_keyboardState != nullptr) {
		if (m_keyboardState[key] == 0)
			return true;
	}
	return false;
}

bool Input::IsMouseDown(MouseInput button)
{
	if (m_mouseButtonStates.size() > 0) {
		if (m_mouseButtonStates[button])
			return true;
	}
	return false;
}

bool Input::IsMouseUp(MouseInput button)
{
	if (m_mouseButtonStates.size() > 0) {
		if (!m_mouseButtonStates[button])
			return true;
	}
	return false;
}

int Input::GetMouseX()
{
	return m_mouseX;
}

int Input::GetMouseY()
{
	return m_mouseY;
}

void Input::GetMousePos(int * x, int * y)
{
	*x = m_mouseX;
	*y = m_mouseY;
}

void Input::OnKeyDown()
{
	m_keyboardState = SDL_GetKeyboardState(0);
}

void Input::OnKeyUp()
{
	m_keyboardState = SDL_GetKeyboardState(0);
}

void Input::OnMouseDown(SDL_Event & e)
{
	// if the event of type mouse down
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		// left mouse button pressed?
		if(e.button.button == SDL_BUTTON_LEFT) 
		{ 
			// left mouse button has been pressed
			m_mouseButtonStates[MOUSE_BUTTON_LEFT] = true; 
		}
		// middle mouse button pressed?
		if (e.button.button == SDL_BUTTON_MIDDLE) 
		{ 
			// middle mouse button has been pressed
			m_mouseButtonStates[MOUSE_BUTTON_MIDDLE] = true; 
		}  
		// right mouse button pressed?
		if (e.button.button == SDL_BUTTON_RIGHT) 
		{ 
			// right mouse button has been pressed
			m_mouseButtonStates[MOUSE_BUTTON_RIGHT] = true; 
		}
		// Get the X position of the mouse on the screen
		m_mouseX = e.button.x;
		// Get the Y position of the mouse on the screen
		m_mouseY = e.button.y;
	}
}

void Input::OnMouseUp(SDL_Event & e)
{
	// if the event of type mouse up
	if (e.type == SDL_MOUSEBUTTONUP) {
		// left mouse button released?
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			m_mouseButtonStates[MOUSE_BUTTON_LEFT] = false;
		}
		// middle mouse button released?
		if (e.button.button == SDL_BUTTON_MIDDLE)
		{
			m_mouseButtonStates[MOUSE_BUTTON_MIDDLE] = false;
		}
		// right mouse button released?
		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			m_mouseButtonStates[MOUSE_BUTTON_RIGHT] = false;
		}
	}
}

void Input::OnMouseMove(SDL_Event & e)
{
	// if it's of type mouse motion
	if (e.type == SDL_MOUSEMOTION) {
		// Get the X position of the mouse on the screen
		m_mouseX = e.button.x;
		// Get the Y position of the mouse on the screen
		m_mouseY = e.button.y;
	}
}

#include "MenuState.h"
#include "Input.h"
#include "FiniteStateMachine.h"
#include "Game.h"
#include "GameState.h"

MenuState::MenuState() {
}

void MenuState::OnEnter() {
	// initialize the text texture
	m_textTexture = new Texture();
	
	// load the font with size
	m_font = TTF_OpenFont("../assets/PressStart2P.ttf", 20);
}

void MenuState::HandleInput(float deltaTime, FiniteStateMachine* fsm) {
	if (Input::GetInstance()->IsKeyDown(SDL_SCANCODE_P)) {
		fsm->PushState(new GameState());
	}
	else if (Input::GetInstance()->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
		Game::GetInstance()->Quit();
	}
	
}

void MenuState::Update(float deltaTime) {

}

void MenuState::Draw(SDL_Renderer* renderer) {
	if (m_font != nullptr) {
		// color of the font
		SDL_Color color = { 255, 255 , 255, 255 };
		if (!m_textTexture->RenderText(("Menu State - Press 'Enter' to play the game & Press'Esc' to Quit."),
			m_font, renderer, color)) {
		}
	}
	m_textTexture->Draw(renderer, 10, 300);
}


void MenuState::OnExit() {
	if (m_textTexture != nullptr) {
		delete m_textTexture;
		m_textTexture = nullptr;
	}
}

MenuState::~MenuState() {
}

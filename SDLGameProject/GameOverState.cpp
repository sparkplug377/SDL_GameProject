#include "GameOverState.h"
#include "Input.h"
#include "FiniteStateMachine.h"
#include "MenuState.h"
#include "Game.h"

GameOverState::GameOverState() {
}

void GameOverState::OnEnter() {
	// initialize the text texture
	m_textTexture = new Texture();

	// load the font with size
	m_font = TTF_OpenFont("../assets/PressStart2P.ttf", 20);
}

void GameOverState::HandleInput(float deltaTime, FiniteStateMachine * fsm) {
	if (Input::GetInstance()->IsKeyDown(SDL_SCANCODE_RETURN)) {
		fsm->PopState();
	}
	if (Input::GetInstance()->IsKeyDown(SDL_SCANCODE_E)) {
		Game::GetInstance()->Quit();
	}
}

void GameOverState::Update(float deltaTime) {
}

void GameOverState::Draw(SDL_Renderer * renderer) {
	if (m_font != nullptr) {
		// color of the font
		SDL_Color color = { 255, 255 , 255, 255 };
		if (!m_textTexture->RenderText(("Game Over State - Press 'Enter' to return to main menu & Press 'E' to Quit."),
			m_font, renderer, color)) {
		}
	}
	m_textTexture->Draw(renderer, 10, 300);
}


void GameOverState::OnExit() {
	if (m_textTexture != nullptr) {
		delete m_textTexture;
		m_textTexture = nullptr;
	}
}

GameOverState::~GameOverState() {
}

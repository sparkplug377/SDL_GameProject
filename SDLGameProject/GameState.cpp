#include "GameState.h"
#include "Game.h"
#include "Input.h"
#include "FiniteStateMachine.h"
#include <string>
#include "GameOverState.h"

GameState::GameState() {
}

void GameState::OnEnter() {
	// initialize player texture
	Texture* animTexture = new Texture();
	// load the texture
	if (animTexture->LoadPNGFromFile("../assets/braid_run.png", 
											Game::GetInstance()->GetRenderer())) {
		SDL_Log("Load player texture - success");
		// initialize player animation
		anim = new Animation(animTexture, 0.03f);
		int texWidth = animTexture->GetImageWidth() / 10;
		int texHeight = animTexture->GetImageHeight() / 3;
		int totalFrames = 26;
		int col = 0;
		int row = 0;
		while (totalFrames >= 0) {
			anim->AddFrame(col * texWidth, row * texHeight, 200, 200);
			++col;
			if (col >= 10) {
				col = 0;
				++row;
			}
			--totalFrames;
		}
	}
	else {
		SDL_Log("Load player texture - failed");
	}

	Texture* playerTexture = new Texture();
	if (playerTexture->LoadPNGFromFile("../assets/ship.png", Game::GetInstance()->GetRenderer())) {
		SDL_Log("Load ship texture - success");

		m_player = new Player(playerTexture, Vector2(Game::GetInstance()->GetWindowWidth() / 2- playerTexture->GetImageWidth()/2, 
												Game::GetInstance()->GetWindowHeight() / 2 - playerTexture->GetImageHeight()/2));

		for (int i = 0; i < 5; ++i) {
			Texture* enemyTexture = new Texture();
			if (enemyTexture->LoadPNGFromFile("../assets/fighter02.png",
										Game::GetInstance()->GetRenderer())) {
				SDL_Log("Load Enemy %i Texture - success", i);
				Vector2 pos = Vector2(i * 10, i * 20);
				m_enemies.push_back(new Enemy(enemyTexture, pos));
			}
			else {
				SDL_Log("Load Enemy %i Texture - failed", i);
			}
		}
	}
	else {
		SDL_Log("Load ship texture - failed");
	}

	// load font
	// initialize the text texture
	m_textTexture = new Texture();

	// load the font with size
	m_font = TTF_OpenFont("../assets/PressStart2P.ttf", 15);

	// load audio
	m_backAudio = Mix_LoadMUS("../assets/audio.mp3");
	if (m_backAudio != nullptr) {
		if (Mix_PlayingMusic() == 0) {
			if (Mix_PlayMusic(m_backAudio, 0) == -1) { }
		}
	}
}

void GameState::HandleInput(float deltaTime, FiniteStateMachine * fsm) {
	// process input from the player
	m_player->HandleInput(deltaTime);

	if (Input::GetInstance()->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
		fsm->ChangeState(new GameOverState());
	}
}

void GameState::Update(float deltaTime) {
	anim->Update(deltaTime);
	m_player->Update(deltaTime);

	// Check player-enemy collision
	PECollisionCheck();

	// check if the font has successfully loaded
	if (m_font != nullptr) {
		// color of the font
		SDL_Color color = { 255, 125 , 0, 255 };
		// rendering text
		std::string sPosX = std::to_string((int)m_player->GetPosition().x);
		std::string sPosY = std::to_string((int)m_player->GetPosition().y);
		if (!m_textTexture->RenderText(("Player Pos, x: " + sPosX + ", y: " + sPosY).c_str(),
			m_font, Game::GetInstance()->GetRenderer(), color)) {
		}
	}

	for (auto itr = m_enemies.begin(); itr != m_enemies.end(); ++itr) {
		(*itr)->Update(deltaTime);
	}
}

void GameState::Draw(SDL_Renderer* renderer) {
	// Render the animation on the screen
	if (anim->GetFrameSize() > 0) {
		anim->Draw(renderer, 100, 200);
	}

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	m_player->Draw(renderer);

	for (GameObject* e : m_enemies) {
		e->Draw(renderer);
	}

	// draw text texture
	m_textTexture->Draw(renderer, 0, 575);
}

void GameState::PECollisionCheck() {
	// collision check between player and enemy
	if (m_player->GetCollider()) {
		for (auto itr = m_enemies.end(); itr != m_enemies.begin();) {
			--itr;
			if ((*itr) != nullptr && m_player->GetCollider()->RectangleCollision(*(*itr)->GetCollider())) {
				delete *itr;
				*itr = nullptr;
				itr = m_enemies.erase(itr);
			}
		}
	}
}

void GameState::OnExit() {
	// deallocate animation
	if (anim != nullptr) {
		delete anim;
		anim = nullptr;
	}

	// deallocate player
	if (m_player != nullptr) {
		delete m_player;
		m_player = nullptr;
	}

	// deallocate the array of enemies
	while (m_enemies.size() > 0) {
		delete m_enemies.back();
		m_enemies.pop_back();
	}

	m_enemies.clear();
	m_enemies.shrink_to_fit();

	if (m_textTexture != nullptr) {
		delete m_textTexture;
		m_textTexture = nullptr;
	}

	if (Mix_PlayingMusic()) { Mix_FadeOutMusic(1000); }

	if (m_backAudio != nullptr) { m_backAudio = nullptr; }
}

GameState::~GameState() {
}

#include "Player.h"


Player::Player() {
	m_position = Vector2(0, 0);
	m_velocity = Vector2(0, 0);
	m_acceleration = Vector2(0, 0);
	m_texture = nullptr;
	SDL_Log("Player Constructor called");
	m_collider = nullptr;
	m_maxVelocity = 0.0f;
	m_input = nullptr;
	m_rotation = 0.0f;
}

Player::Player(Texture * texture, Vector2 pos) {
	m_texture = texture;
	this->m_position = pos;
	m_velocity = Vector2(0, 0);
	m_acceleration = Vector2(0, 0);
	// set up the collider
	m_collider = new AABB(m_position, m_texture->GetImageWidth(), m_texture->GetImageHeight());
	m_maxVelocity = 200.0f;
	m_input = nullptr;
	m_rotation = 0.0f;
}

void Player::Update(float deltaTime) {
	// ambiguous formula for 2D rotation
	// x' = x cos f - y sin f
	// y' = y cos f + x sin f
	//Vector2 direction = Vector2(0,0);
	//direction.x = m_velocity.x * cosf(m_rotation * deltaTime) - m_velocity.y * sinf(m_rotation * deltaTime);
	//direction.y = m_velocity.y * cosf(m_rotation * deltaTime) + m_velocity.x * sinf(m_rotation * deltaTime);

	// applying friction
	SetForce(m_velocity * -.99f);
	// change the speed based on acceleration
	m_velocity += m_acceleration * deltaTime;
	SDL_Log("Velocity: %f, %f", m_velocity.x, m_velocity.y);

	// setting up max velocity
	float length = m_velocity.Magnitude();
	if (length >= m_maxVelocity) {
		m_velocity.Normalize();
		m_velocity = m_velocity * m_maxVelocity;
	}

	// change the position based on the velocity
	m_position += m_velocity * deltaTime;
	SDL_Log("Velocity: %f, %f", m_position.x, m_position.y);

	m_acceleration = Vector2(0, 0);

	// update AABB
	m_collider->Update(m_position);
}

void Player::Draw(SDL_Renderer* renderer) {
	// draw the texture that includes rotation
	m_texture->DrawEx(renderer, m_position.x, m_position.y, NULL, m_rotation);

	SDL_Rect rect = { m_collider->GetPosition().x, m_collider->GetPosition().y,
		m_collider->GetWidth(), m_collider->GetHeight() };
	SDL_RenderDrawRect(renderer, &rect);
}

void Player::HandleInput(float deltaTime) {
	m_input = Input::GetInstance();
	// convert degrees to radians
	float angle = (3.1415926535897f * m_rotation) / 180.0f;

	if (m_input->IsKeyDown(SDL_SCANCODE_W)) {
		// direction the player is currently facing
		Vector2 direction = Vector2(0, 0);
		direction.x = sin(angle);
		direction.y = -cos(angle);
		// move the player in that direction
		SetForce(direction * 100.0f);
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_S)) {
		// direction the player is currently facing
		Vector2 direction = Vector2(0, 0);
		direction.x = -sin(angle);
		direction.y = cos(angle);
		// move the player in that direction
		SetForce(direction * 100.0f);
	}

	if (m_input->IsKeyDown(SDL_SCANCODE_A)) {
		// rotate the player
		m_rotation -= 100.0f * deltaTime;
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_D)) {
		// rotate the player
		m_rotation += 100.0f * deltaTime;
	}

	// Move the player using mouse
	//int x = 0;
	//int y = 0;
	//m_input->GetMousePos(&x, &y);
	//if (m_input->IsMouseDown(MOUSE_BUTTON_LEFT)) {
	//	SetForce(Vector2(x - m_position.x, y - m_position.y));
	//}
}

void Player::SetForce(Vector2 force)
{
	m_acceleration += force;
}

Vector2 Player::GetVelocity()
{
	return m_velocity;
}

AABB * Player::GetCollider()
{
	return m_collider;
}

Player::~Player() {
	SDL_Log("Player Destructor called");
	// deletes the AABB
	if (m_collider != nullptr) {
		delete m_collider;
		m_collider = nullptr;
	}
}

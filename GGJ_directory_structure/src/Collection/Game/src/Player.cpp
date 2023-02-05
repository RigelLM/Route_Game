#include "Player.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include "GameCore.h"

Player::Player()
{
}

void Player::LoadAssets()
{
	left.reset(new Illusion::SequenceAnimation(8, "assets/animations/Player/move/left", "Left"));
	right.reset(new Illusion::SequenceAnimation(8, "assets/animations/Player/move/right", "Right"));
	up.reset(new Illusion::SequenceAnimation(8, "assets/animations/Player/move/up", "Up"));
	down.reset(new Illusion::SequenceAnimation(8, "assets/animations/Player/move/down", "Down"));

	stay_left.reset(new Illusion::SequenceAnimation(1, "assets/animations/Player/stay/left", "Left"));
	stay_right.reset(new Illusion::SequenceAnimation(1, "assets/animations/Player/stay/right", "Right"));
	stay_up.reset(new Illusion::SequenceAnimation(1, "assets/animations/Player/stay/up", "Up"));
	stay_down.reset(new Illusion::SequenceAnimation(1, "assets/animations/Player/stay/down", "Down"));

	m_MoveAnims[Left] = left;
	m_MoveAnims[Right] = right;
	m_MoveAnims[Up] = up;
	m_MoveAnims[Down] = down;

	m_StayAnims[Left] = stay_left;
	m_StayAnims[Right] = stay_right;
	m_StayAnims[Up] = stay_up;
	m_StayAnims[Down] = stay_down;
}

void Player::OnUpdate(Illusion::Timestep ts, glm::vec2 spawn)
{
	if (MapState != LastMap)
	{
		Reset(spawn);
		LastMap = MapState;
	}

	bool up = Illusion::Input::IsKeyPressed(ILLUSION_KEY_W) || Illusion::Input::IsKeyPressed(ILLUSION_KEY_UP);
	bool down = Illusion::Input::IsKeyPressed(ILLUSION_KEY_S) || Illusion::Input::IsKeyPressed(ILLUSION_KEY_DOWN);
	bool left = Illusion::Input::IsKeyPressed(ILLUSION_KEY_A) || Illusion::Input::IsKeyPressed(ILLUSION_KEY_LEFT);
	bool right = Illusion::Input::IsKeyPressed(ILLUSION_KEY_D) || Illusion::Input::IsKeyPressed(ILLUSION_KEY_RIGHT);

	bool move = up || down || left || right;

	AT h = NONE;
	AT v = NONE;

	if (move)
	{
		m_Moving = true;

		if (right)
		{
			h = RIGHT;
			m_Velocity = glm::vec2(5.0f, 0.0f);
			m_Position += m_Velocity * (float)ts;
		}
		else if (left)
		{
			h = LEFT;
			m_Velocity = glm::vec2(-5.0f, 0.0f);
			m_Position += m_Velocity * (float)ts;
		}
		else if (down)
		{
			v = DOWN;
			m_Velocity = glm::vec2(0.0f, -5.0f);
			m_Position += m_Velocity * (float)ts;
		}
		else if (up)
		{
			v = UP;
			m_Velocity = glm::vec2(0.0f, 5.0f);
			m_Position += m_Velocity * (float)ts;
		}

		if (!((h | v) ^ (LEFT)))
			m_AnimType = Left;
		else if (!((h | v) ^ (RIGHT)))
			m_AnimType = Right;
		else if (!((h | v) ^ (DOWN)))
			m_AnimType = Down;
		else if (!((h | v) ^ (UP)))
			m_AnimType = Up;
	}
	else
	{
		m_Moving = false;
	}

	ColliderInfo info
	{
		Circle,
		glm::vec2(m_Position.x - 0.1f, m_Position.y - 1.5f ),
		glm::vec2(0.0f,0.0f),
		m_ColliderRadius
	};
	m_Collider.Init(info);

}
void Player::OnRender()
{
	if (m_Moving)
		m_MoveAnims[m_AnimType]->Play({ m_Position.x, m_Position.y, 0.5f }, { 2.4f, 5.0f }, 1.25f, false);
	else
		m_StayAnims[m_AnimType]->Play({ m_Position.x, m_Position.y, 0.5f }, { 2.4f, 5.0f }, 1.0f, false);
}

void Player::Reset(glm::vec2 spawn)
{
	m_Position = spawn;
	m_Velocity = { 5.0f, 0.0f };	
}


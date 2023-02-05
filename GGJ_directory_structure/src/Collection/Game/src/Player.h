#pragma once

#include <Engine.h>

#include "Collider.h"

class Player
{
public:
	Player();

	void LoadAssets();

	void OnUpdate(Illusion::Timestep ts, glm::vec2 spawn);
	void OnRender();

	void Reset(glm::vec2 spawn);

	Collider GetCollider() { return m_Collider; }

	const glm::vec2& GetPosition() const { return m_Position; }

	void SetPosition(glm::vec2 pos) { m_Position = pos; }

private:
	glm::vec2 m_Position = { 0.0f, 0.0f };
	glm::vec2 m_Velocity = { 5.0f, 0.0f };

	enum AT
	{
		NONE		= 0,
		LEFT		= BIT(1),
		RIGHT		= BIT(2),
		UP			= BIT(3),
		DOWN		= BIT(4),
	};

	enum Animation
	{
		Left, Right, Up, Down
	};

	Animation m_AnimType = Right;
	bool m_Moving = false;

	Illusion::Ref<Illusion::SequenceAnimation> left, right, up, down;

	Illusion::Ref<Illusion::SequenceAnimation> stay_left, stay_right, stay_up, stay_down;

	std::unordered_map<Animation, Illusion::Ref<Illusion::SequenceAnimation>> m_MoveAnims, m_StayAnims;

	Collider m_Collider;
	float m_ColliderRadius = 1.0f;
};
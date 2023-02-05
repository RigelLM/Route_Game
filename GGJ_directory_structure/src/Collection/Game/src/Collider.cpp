#include "Collider.h"

void Collider::Init(ColliderInfo& info)
{
	m_Info = info;
}

Collision Collider::Test(Collider& target)
{
	if (m_Info.type == Box && target.GetInfo().type == Circle)
	{
		glm::vec2 center = target.GetInfo().position;
		glm::vec2 aabb_half_extents = m_Info.size / 2.0f;
		glm::vec2 aabb_center(
			m_Info.position.x - 0.25f,
			m_Info.position.y
		);
		glm::vec2 difference = center - aabb_center;
		glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
		glm::vec2 closest = aabb_center + clamped;
		difference = closest - center;
		if (glm::length(difference) < target.GetInfo().radius)
			return std::make_tuple(true, CollideDir(difference), difference);
		else
			return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
	}

}

void Collider::Process(Collision& collision)
{
}
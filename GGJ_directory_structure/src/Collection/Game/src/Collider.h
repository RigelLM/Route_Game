#pragma once

#include <Engine.h>

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

enum ColliderType
{
	Circle, Box
};

struct ColliderInfo
{
	ColliderType type = Box;
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	glm::vec2 size = glm::vec2(1.0f,1.0f);
	float radius = 1.0f;
};

class Collider
{

public:

	Collider() {};

	void Init(ColliderInfo& info);

	Collision Test(Collider& target);

	void Process(Collision& collision);

	const ColliderInfo GetInfo() { return m_Info; }

private:

	inline Direction CollideDir(glm::vec2 target)
	{
		glm::vec2 compass[] =
		{
			glm::vec2(0.0f, 1.0f),  // up
			glm::vec2(1.0f, 0.0f),  // right
			glm::vec2(0.0f, -1.0f), // down
			glm::vec2(-1.0f, 0.0f)  // left
		};
		float max = 0.0f;
		int best_match = -1;
		for (int i = 0; i < 4; i++)
		{
			float dot_product = glm::dot(glm::normalize(target), compass[i]);
			if (dot_product > max)
			{
				max = dot_product;
				best_match = i;
			}
		}
		return (Direction)best_match;
	}

private:

	ColliderInfo m_Info;

};


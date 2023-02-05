#include "Level.h"

#include "Engine/Core/Utils/Random.h"

#include <glm/gtc/matrix_transform.hpp>

#include "GameCore.h"


void Level::Init()
{
	m_BGMPlayer.reset(new Illusion::SoundPlayer("assets/sounds/musics/music.mp3"));
	m_BGMPlayer->Play();

	Illusion::Ref<Map> town = std::make_shared<Town_Map>(glm::vec2(51.2f, 43.2f));
	town->LoadAssets("assets/textures/town/day.png");
	m_Maps["town"] = town;

	Illusion::Ref<Map> hotel_room = std::make_shared<Hotel_Room_Map>(glm::vec2(25.0f, 14.40f));
	hotel_room->LoadAssets("assets/textures/hotel_room/room.png");
	m_Maps["hotel_room"] = hotel_room;

	Illusion::Ref<Map> docter_room = std::make_shared<Docter_Room_Map>(glm::vec2(25.0f, 14.40f));
	docter_room->LoadAssets("assets/textures/docter_room/room.png");
	m_Maps["docter_room"] = docter_room;

	Illusion::Ref<Map> townhall_room = std::make_shared<Townhall_Room_Map>(glm::vec2(25.0f, 14.40f));
	townhall_room->LoadAssets("assets/textures/townhall_room/room.png");
	m_Maps["townhall_room"] = townhall_room;

	m_Player.LoadAssets();
}

void Level::OnUpdate(Illusion::Timestep ts)
{
	m_BGMPlayer->OnUpdate();

	std::string MapName = "town";
	if (MapState == town)
	{
		MapName = "town";
	}
	else if (MapState == hotel_room)
	{
		MapName = "hotel_room";
	}
	else if (MapState == docter_room)
	{
		MapName = "docter_room";
	}
	else if (MapState == townhall_room)
	{
		MapName = "townhall_room";
	}

	m_Player.OnUpdate(ts, m_Maps[MapName.c_str()]->m_SpawnPoint);

	m_Maps[MapName.c_str()]->OnUpdate(ts, m_Player);
	Collision collision = m_Maps[MapName.c_str()]->CollistionTest(m_Player);
	if (std::get<0>(collision)) // ���collision �� true
	{
		// ��ײ����
		Direction dir = std::get<1>(collision);
		glm::vec2 diff_vector = std::get<2>(collision);
		if (dir == LEFT || dir == RIGHT) // ˮƽ������ײ
		{
			// �ض�λ
			float penetration = 1.0f - std::abs(diff_vector.x);
			if (dir == LEFT)
				m_Player.SetPosition(glm::vec2(m_Player.GetPosition().x + penetration, m_Player.GetPosition().y)); // ��������
			else
				m_Player.SetPosition(glm::vec2(m_Player.GetPosition().x - penetration, m_Player.GetPosition().y)); // ��������
		}
		else // ��ֱ������ײ
		{
			// �ض�λ
			float penetration = 1.0f - std::abs(diff_vector.y);
			if (dir == UP)
				m_Player.SetPosition(glm::vec2(m_Player.GetPosition().x, m_Player.GetPosition().y - penetration)); // ��������
			else
				m_Player.SetPosition(glm::vec2(m_Player.GetPosition().x, m_Player.GetPosition().y + penetration)); // ��������
		}

	}

}

void Level::OnEvent(Illusion::Event& e)
{
	std::string MapName = "town";
	if (MapState == town)
	{
		MapName = "town";
	}
	else if (MapState == hotel_room)
	{
		MapName = "hotel_room";
	}
	else if (MapState == docter_room)
	{
		MapName = "docter_room";
	}
	else if (MapState == townhall_room)
	{
		MapName = "townhall_room";
	}
	m_Maps[MapName.c_str()]->OnEvent(e, m_Player);
}

void Level::OnRender()
{
	const auto& playerPos = m_Player.GetPosition();

	// Background
	Illusion::Renderer2D::DrawQuad({ playerPos.x, 0.0f, -0.8f }, { 50.0f, 50.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });

	std::string MapName = "town";
	if (MapState == town)
	{
		MapName = "town";
	}
	else if (MapState == hotel_room)
	{
		MapName = "hotel_room";
	}
	else if (MapState == docter_room)
	{
		MapName = "docter_room";
	}
	else if (MapState == townhall_room)
	{
		MapName = "townhall_room";
	}
	m_Maps[MapName.c_str()]->OnRender();

	m_Player.OnRender();
}

void Level::GameOver()
{
	m_GameOver = true;
}
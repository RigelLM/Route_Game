#include "Map.h"

#include <imgui/imgui.h>

#include "GameCore.h"

Map::Map(glm::vec2 size)
	:m_Size(size)
{
	m_SpawnPoint = glm::vec2(0.0f, 0.0f);
}
void Map::LoadAssets(std::string path)
{
	m_MapTexture.reset(new Illusion::Texture2D(path));
	for (auto& go : m_GameObjects)
	{
		go->LoadAssets();
	}
}
void Map::OnUpdate(Illusion::Timestep ts, Player& p)
{
	for (auto& go : m_GameObjects)
	{
		go->OnUpdate(p.GetCollider());
	}
}
void Map::OnEvent(Illusion::Event& e, Player& p)
{
	for (auto& go : m_GameObjects)
	{
		go->OnEvent(e, p.GetCollider());
	}
}
void Map::OnRender()
{
	Illusion::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, 0.0f), m_Size, m_MapTexture);
	for (auto& go : m_GameObjects)
	{
		go->OnRender();
	}
}
void Map::OnImGuiRender()
{

}
Collision Map::CollistionTest(Player& p)
{
	for (auto& go : m_GameObjects)
	{
		Collision result = go->CollisionTest(p.GetCollider());
		if (std::get<0>(result))
		{
			return result;
		}
	}
	for (auto& colliders : m_Walls)
	{
		Collision result = colliders->Test(p.GetCollider());
		if (std::get<0>(result))
		{
			return result;
		}
	}
	return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}


Town_Map::Town_Map(glm::vec2 size)
	:Map(size)
{
	m_SpawnPoint = glm::vec2(20.0f, 0.0f);


	m_Back.reset(new Illusion::SequenceAnimation(1, "assets/textures/text/background", "back"));

	m_Traveler.reset(new NPC("assets/textures/NPC/start.png", "assets/textures/text/start", 9, 40.0f, "start"));
	info[15].position = glm::vec3(23.0f, -1.5f, 0.4f);
	info[15].size = glm::vec2(1.0f, 1.0f);
	m_Traveler->Init(true, glm::vec3(23.0f, 0.0f, 0.4f), glm::vec2(1.0, 1.0f), info[15]);
	m_GameObjects.push_back(m_Traveler);

	m_Day.reset(new Illusion::Texture2D("assets/textures/town/day.png"));
	m_Night.reset(new Illusion::Texture2D("assets/textures/town/night.png"));

	Illusion::Ref<Door> docter = std::make_shared<Door>("assets/textures/hotel_room/DOOR_FRONT.png", docter_room, true);
	info[0].position = glm::vec3(-52.2f / 2.0f / 4.0f * 3.0f + 7.5f, -12.35f, 0.4f);
	info[0].size = glm::vec2(2.75f, 1.0f);
	docter->Init(true, glm::vec3(-52.2f / 2.0f / 4.0f * 3.0f + 7.5f, -12.35f, 0.4f), 2.05f * glm::vec2(2.75f, 1.0f), info[0]);
	m_GameObjects.push_back(docter);

	Illusion::Ref<Door> hotel = std::make_shared<Door>("assets/textures/hotel_room/DOOR_FRONT.png", hotel_room, true);
	info[1].position = glm::vec3(4.75f, 1.0f, 0.4f);
	info[1].size = glm::vec2(1.0f, 2.75f);
	hotel->Init(true, glm::vec3(4.75f, 1.0f, 0.4f), 2.05f * glm::vec2(1.0f, 2.75f), info[1]);
	m_GameObjects.push_back(hotel);

	Illusion::Ref<Door> townhall = std::make_shared<Door>("assets/textures/hotel_room/DOOR_FRONT.png", townhall_room, true);
	info[2].position = glm::vec3(-52.2f / 2.0f / 4.0f * 3.0f + 0.75f, -0.5, 0.4f);
	info[2].size = glm::vec2(1.0f, 2.75f);
	townhall->Init(true, glm::vec3(-52.2f / 2.0f / 4.0f * 3.0f + 0.75f, -0.5, 0.4f), 2.05f * glm::vec2(1.0f, 2.75f), info[2]);
	m_GameObjects.push_back(townhall);

	info[3].position = glm::vec3(0.00f, 43.2f / 2.0f - 4.0f, 0.4f);
	info[4].position = glm::vec3(52.2f / 2.0f, 0.0f, 0.4f);
	info[5].position = glm::vec3(0.00f, -43.2f / 2.0f + 2.0f, 0.4f);
	info[6].position = glm::vec3(-52.2f / 2.0f, 0.00f, 0.4f);
	info[7].position = glm::vec3(52.2f / 2.0f / 4.0f * 3.0f, -10.0f - 3.0f, 0.4f);
	info[8].position = glm::vec3(52.2f / 2.0f / 4.0f * 3.0f + 0.5f, 10.0f + 1.0f, 0.4f);
	info[9].position = glm::vec3(2.25f, 4.5f, 0.4f);
	info[10].position = glm::vec3(2.25f, -10.0f, 0.4f);
	info[11].position = glm::vec3(52.2f / 2.8f / 2.0f + 2.0f, -3.0f, 0.4f);
	info[12].position = glm::vec3(-52.2f / 2.0f / 4.0f * 3.0f - 0.75f, -10.5f, 0.4f);
	info[13].position = glm::vec3(-52.2f / 2.0f / 4.0f * 3.0f - 0.5f, 5.0f, 0.4f);
	info[14].position = glm::vec3(-52.2f / 2.0f / 4.0f * 3.0f - 4.5f, 15.0f, 0.4f);
	info[3].size = glm::vec2(51.2f, 1.00f);
	info[4].size = glm::vec2(1.00f, 43.2f);
	info[5].size = glm::vec2(51.2f, 1.00f);
	info[6].size = glm::vec2(1.00f, 43.2f);
	info[7].size = glm::vec2(43.2f / 4.5f, 52.2f / 2.8f);
	info[8].size = glm::vec2(43.2f / 4.5f, 52.2f / 2.8f);
	info[9].size = glm::vec2(52.2f / 2.8f, 43.2f / 4.5f);
	info[10].size = glm::vec2(52.2f / 2.8f, 43.2f / 4.5f);
	info[11].size = glm::vec2(0.75f, 43.2f / 4.5f * 2.5f);
	info[12].size = glm::vec2(52.2f / 2.8f, 43.2f / 4.5f);
	info[13].size = glm::vec2(52.2f / 2.8f, 52.2f / 2.8f - 6.0f);
	info[14].size = glm::vec2(52.2f / 2.8f, 52.2f / 2.8f - 8.0f);

	Illusion::Ref<Collider> m_Up = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Left = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Down = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Right = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_RightDown = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_RightUp = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_hotel = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_hotelDown = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_hotelRight = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Docter = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_hall = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_hallUp = std::make_shared<Collider>();

	m_Up->Init(info[3]);
	m_Left->Init(info[4]);
	m_Down->Init(info[5]);
	m_Right->Init(info[6]);
	m_RightDown->Init(info[7]);
	m_RightUp->Init(info[8]);
	m_hotel->Init(info[9]);
	m_hotelDown->Init(info[10]);
	m_hotelRight->Init(info[11]);
	m_Docter->Init(info[12]);
	m_hall->Init(info[13]);
	m_hallUp->Init(info[14]);

	m_Walls.push_back(m_Up);
	m_Walls.push_back(m_Left);
	m_Walls.push_back(m_Down);
	m_Walls.push_back(m_Right);
	m_Walls.push_back(m_RightDown);
	m_Walls.push_back(m_RightUp);
	m_Walls.push_back(m_hotel);
	m_Walls.push_back(m_hotelDown);
	m_Walls.push_back(m_hotelRight);
	m_Walls.push_back(m_Docter);
	m_Walls.push_back(m_hall);
	m_Walls.push_back(m_hallUp);

}
void Town_Map::OnUpdate(Illusion::Timestep ts, Player& p)
{
	if (GameTime == day)
		m_MapTexture = m_Day;
	else
		m_MapTexture = m_Night;

	for (auto& go : m_GameObjects)
	{
		go->OnUpdate(p.GetCollider());
	}
}


Hotel_Room_Map::Hotel_Room_Map(glm::vec2 size)
	:Map(size)
{
	m_SpawnPoint = glm::vec2(10.0f, -3.0f);

	Illusion::Ref<GameObject> bed = std::make_shared<Bed>("assets/textures/hotel_room/BED.png");
	Illusion::Ref<GameObject> chair = std::make_shared<GameObject>("assets/textures/hotel_room/CHAIR.png");
	Illusion::Ref<GameObject> desk = std::make_shared<GameObject>("assets/textures/hotel_room/DESK.png");
	Illusion::Ref<Paint> pic = std::make_shared<Paint>("assets/textures/hotel_room/PIC3.png");
	Illusion::Ref<Door> door = std::make_shared<Door>("assets/textures/hotel_room/DOOR_FRONT.png", town, false);
	Illusion::Ref<Door> door_side = std::make_shared<Door>("assets/textures/hotel_room/DOOR_SIDE.png", town, false);

	info[0].position = glm::vec3(-8.97f, 0.05f, 0.4f);
	info[1].position = glm::vec3(-7.60f, -4.635f, 0.4f);
	info[2].position = glm::vec3(-11.05f, -4.4f, 0.4f);
	info[3].position = glm::vec3(7.5f, 4.0f, 0.4f);
	info[4].position = glm::vec3(3.5f, 3.450f, 0.4f);
	info[5].position = glm::vec3(12.0f, -1.7f, 0.4f);

	info[0].size = glm::vec2(5.00f, 2.68f);
	info[1].size = glm::vec2(2.50f, 2.50f);
	info[2].size = glm::vec2(1.84f, 3.30f);
	info[3].size = glm::vec2(1.12f, 7.30f);
	info[4].size = glm::vec2(2.00f, 6.00f);
	info[5].size = glm::vec2(0.50f, 8.00f);

	info[6].position = glm::vec3(0.00f, 1.00f, 0.4f);
	info[7].position = glm::vec3(-12.0f, 0.0f, 0.4f);
	info[8].position = glm::vec3(0.00f, -7.0f, 0.4f);
	info[9].position = glm::vec3(12.5f, 0.00f, 0.4f);
	info[6].size = glm::vec2(25.0f, 1.00f);
	info[7].size = glm::vec2(1.00f, 10.0f);
	info[8].size = glm::vec2(25.0f, 1.00f);
	info[9].size = glm::vec2(1.00f, 10.0f);

	Illusion::Ref<Collider> m_Up = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Left = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Down = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Right = std::make_shared<Collider>();

	m_Up->Init(info[6]);
	m_Left->Init(info[7]);
	m_Down->Init(info[8]);
	m_Right->Init(info[9]);

	m_Walls.push_back(m_Up);
	m_Walls.push_back(m_Left);
	m_Walls.push_back(m_Down);
	m_Walls.push_back(m_Right);

	bed->Init(true, glm::vec3(-8.97f, 0.05f, 0.4f), 1.5f * glm::vec2(4.14f, 2.68f), info[0]);
	chair->Init(false, glm::vec3(-7.60f, -4.635f, 0.4f), 1.8f * glm::vec2(2.5f, 2.5f), info[1]);
	desk->Init(false, glm::vec3(-11.05f, -4.4f, 0.4f), 1.5f * glm::vec2(1.84f, 3.30f), info[2]);
	pic->Init(true, glm::vec3(7.5f, 4.5f, 0.4f), 2.0f * glm::vec2(1.12f, 1.30f), info[3]);
	door->Init(true, glm::vec3(3.5f, 3.450f, 0.4f), 2.05f * glm::vec2(1.57f, 3.07f), info[4]);
	door_side->Init(true, glm::vec3(11.55f, -1.7f, 0.4f), 2.2f * glm::vec2(0.82f, 4.80f), info[5]);

	m_GameObjects.push_back(bed);
	m_GameObjects.push_back(chair);
	m_GameObjects.push_back(desk);
	m_GameObjects.push_back(pic);
	m_GameObjects.push_back(door);
	m_GameObjects.push_back(door_side);
}


Townhall_Room_Map::Townhall_Room_Map(glm::vec2 size)
	:Map(size)
{
	m_SpawnPoint = glm::vec2(10.0f, -3.0f);

	m_Traveler.reset(new NPC("assets/textures/NPC/townhall.png", "assets/textures/text/townhall", 5, 40.0f, "townhall"));
	info[1].position = glm::vec3(0.0f, -1.5f, 0.4f);
	info[1].size = glm::vec2(1.0f, 1.0f);
	m_Traveler->Init(true, glm::vec3(0.0f, 0.0f, 0.4f), glm::vec2(1.0, 1.0f), info[1]);
	m_GameObjects.push_back(m_Traveler);

	Illusion::Ref<Door> door_side = std::make_shared<Door>("assets/textures/hotel_room/DOOR_SIDE.png", town, false);
	info[5].position = glm::vec3(10.0f, 0.0f, 0.4f);
	info[5].size = glm::vec2(1.0f, 8.00f);
	door_side->Init(true, glm::vec3(10.0f, 0.0f, 0.4f),glm::vec2(1.00f, 8.00f), info[5]);
	m_GameObjects.push_back(door_side);


	info[6].position = glm::vec3(0.00f, 6.00f, 0.4f);
	info[7].position = glm::vec3(-12.0f, 0.0f, 0.4f);
	info[8].position = glm::vec3(0.00f, -7.0f, 0.4f);
	info[9].position = glm::vec3(12.5f, 0.00f, 0.4f);
	info[6].size = glm::vec2(25.0f, 1.00f);
	info[7].size = glm::vec2(1.00f, 10.0f);
	info[8].size = glm::vec2(25.0f, 1.00f);
	info[9].size = glm::vec2(1.00f, 10.0f);

	Illusion::Ref<Collider> m_Up = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Left = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Down = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Right = std::make_shared<Collider>();

	m_Up->Init(info[6]);
	m_Left->Init(info[7]);
	m_Down->Init(info[8]);
	m_Right->Init(info[9]);

	m_Walls.push_back(m_Up);
	m_Walls.push_back(m_Left);
	m_Walls.push_back(m_Down);
	m_Walls.push_back(m_Right);
}


Docter_Room_Map::Docter_Room_Map(glm::vec2 size)
	:Map(size)
{
	m_SpawnPoint = glm::vec2(9.0f, 0.0f);

	m_Docter.reset(new NPC("assets/textures/NPC/doctor.png", "assets/textures/text/doctor", 3, 30.0f, "doctor"));
	info[8].position = glm::vec3(-4.0f, -1.5f, 0.4f);
	info[8].size = glm::vec2(1.0f, 1.0f);
	m_Docter->Init(true, glm::vec3(-4.0f, 0.0f, 0.4f), glm::vec2(1.0, 1.0f), info[8]);
	m_GameObjects.push_back(m_Docter);

	m_CluePic.reset(new Illusion::Texture2D("assets/textures/clues/mosscode.png"));

	m_MossCode.reset(new Illusion::SequenceAnimation(43, "assets/animations/MossCode", "MossCode"));

	Illusion::Ref<Door> door_side = std::make_shared<Door>("assets/textures/docter_room/door_side.png", town, false);
	Illusion::Ref<GameObject> piano = std::make_shared<GameObject>("assets/textures/docter_room/chair.png");
	info[0].position = glm::vec3(12.0f, -1.7f, 0.4f);
	info[1].position = glm::vec3(-9.5f, 0.50f, 0.4f);
	info[0].size = glm::vec2(0.50f, 8.00f);
	info[1].size = glm::vec2(3.00f, 3.00f);
	door_side->Init(true, glm::vec3(11.68f, -0.18f, 0.4f), 2.2f * glm::vec2(0.22f, 3.89f), info[0]);
	piano->Init(false, glm::vec3(-8.73f, 0.75f, 0.4f), 2.0f * glm::vec2(0.8f, 1.75f), info[1]);
	m_GameObjects.push_back(door_side);
	m_GameObjects.push_back(piano);

	info[1 + 1].position = glm::vec3(0.00f, 2.00f, 0.4f);
	info[2 + 1].position = glm::vec3(-9.5f, 0.0f, 0.4f);
	info[3 + 1].position = glm::vec3(0.00f, -7.0f, 0.4f);
	info[4 + 1].position = glm::vec3(12.5f, 0.00f, 0.4f);
	info[5 + 1].position = glm::vec3(7.80f, 1.50f, 0.4f);
	info[6 + 1].position = glm::vec3(3.75f, -4.5f, 0.4f);
	info[1 + 1].size = glm::vec2(25.0f, 1.00f);
	info[2 + 1].size = glm::vec2(1.00f, 10.0f);
	info[3 + 1].size = glm::vec2(25.0f, 1.00f);
	info[4 + 1].size = glm::vec2(1.00f, 10.0f);
	info[5 + 1].size = glm::vec2(1.80f, 2.50f);
	info[6 + 1].size = glm::vec2(3.00f, 6.00f);

	Illusion::Ref<Collider> m_Up = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Left = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Down = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Right = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Stuff = std::make_shared<Collider>();
	Illusion::Ref<Collider> m_Stuff2 = std::make_shared<Collider>();

	m_Up->Init(info[1 + 1]);
	m_Left->Init(info[2 + 1]);
	m_Down->Init(info[3 + 1]);
	m_Right->Init(info[4 + 1]);
	m_Stuff->Init(info[5 + 1]);
	m_Stuff2->Init(info[6 + 1]);

	m_Walls.push_back(m_Up);
	m_Walls.push_back(m_Left);
	m_Walls.push_back(m_Down);
	m_Walls.push_back(m_Right);
	m_Walls.push_back(m_Stuff);
	m_Walls.push_back(m_Stuff2);
}
void Docter_Room_Map::OnEvent(Illusion::Event& e, Player& p)
{
	for (auto& go : m_GameObjects)
	{
		go->OnEvent(e, p.GetCollider());
	}
	Illusion::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Illusion::MouseButtonPressedEvent>(ENGINE_BIND_EVENT_FN(Docter_Room_Map::OnMouseButtonPressed));
}
bool Docter_Room_Map::OnMouseButtonPressed(Illusion::MouseButtonPressedEvent& e)
{
	if (!m_Firsttime)
	{
		m_Active = !m_Active;
	}

	return false;

}
void Docter_Room_Map::OnRender()
{
	m_MossCode->Play(glm::vec3(0.0f, 0.0f, 0.0f), m_Size, 20.0f, true);
	if (m_MossCode->Check() && m_Firsttime == true)
	{
		m_Active = true;
		m_Firsttime = false;
	}

	if (m_Active)
		Illusion::Renderer2D::DrawUIQuad(glm::vec3(0.0f, 0.0f, -0.5f), { 2.0f * 0.692f, 2.0f * 0.509f }, m_CluePic);

	for (auto& go : m_GameObjects)
	{
		go->OnRender();
	}
}


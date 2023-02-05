#pragma once

#include <Engine.h>

#include "GameObject.h"
#include "Player.h"

class Map
{
public:

	Map(glm::vec2 size);

	void LoadAssets(std::string path);
	virtual void OnUpdate(Illusion::Timestep ts, Player& p);
	virtual void OnEvent(Illusion::Event& e, Player& p);
	virtual void OnRender();
	Collision CollistionTest(Player& p);
	void OnImGuiRender();

	glm::vec2 m_SpawnPoint;
	glm::vec2 m_Size;
	Illusion::Ref<Illusion::Texture2D> m_MapTexture;
	std::vector<Illusion::Ref<GameObject>> m_GameObjects;
	std::vector<Illusion::Ref<Collider>> m_Walls;
};

class Town_Map : public Map
{
public:
	Town_Map(glm::vec2 size);

	void OnUpdate(Illusion::Timestep ts, Player& p) override;
private:
	ColliderInfo info[20];
	Illusion::Ref<Illusion::Texture2D> m_Day;
	Illusion::Ref<Illusion::Texture2D> m_Night;

	Illusion::Ref<Illusion::SequenceAnimation> m_Back;

	Illusion::Ref<NPC> m_Traveler;


	bool m_Active = false;
	bool m_Firsttime = true;
};

class Hotel_Room_Map : public Map
{
public:
	Hotel_Room_Map(glm::vec2 size);
private:
	ColliderInfo info[10];
};

class Townhall_Room_Map : public Map
{
public:
	Townhall_Room_Map(glm::vec2 size);
private:
	ColliderInfo info[10];

	Illusion::Ref<NPC> m_Traveler;

};

class Docter_Room_Map : public Map
{
public:
	Docter_Room_Map(glm::vec2 size);
	void OnEvent(Illusion::Event& e, Player& p) override;
	bool OnMouseButtonPressed(Illusion::MouseButtonPressedEvent& e);
	void OnRender() override;
private:
	ColliderInfo info[9];
	Illusion::Ref<Illusion::Texture2D> m_CluePic;
	Illusion::Ref<Illusion::SequenceAnimation> m_MossCode;

	Illusion::Ref<NPC> m_Docter;

	bool m_Active = false;
	bool m_Firsttime = true;

};
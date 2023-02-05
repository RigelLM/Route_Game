#pragma once

#include "Collider.h"
#include "Engine/Core/Utils/Timer.h"
#include "GameCore.h"


class GameObject
{
public:

	GameObject(std::string textpath);

	virtual void Init(bool inter, glm::vec3 pos, glm::vec2 size, ColliderInfo& info);
	void LoadAssets();

	virtual void OnUpdate(Collider& c);

	virtual void OnRender();

	Collision CollisionTest(Collider& col);
	Collider GetCollider() { return m_Collider; }

	const glm::vec2& GetPosition() const { return m_Position; }

	virtual void OnEvent(Illusion::Event& e, Collider& c);
	virtual bool OnKeyPressed(Illusion::KeyPressedEvent& e);

public:
	Illusion::Ref<Illusion::Texture2D> m_Notice;

	Illusion::Ref<Illusion::Texture2D> m_Texture;

	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	glm::vec2 m_Size = { 1.0f,1.0f };

	float m_DetectRadius = 3.5f;

	bool m_Interactable = false;

	bool m_Detected = false;

	Collider m_Collider;

};

class NPC : public GameObject
{
public:
	NPC(std::string path, std::string text, int frame, float time, std::string name);
	void OnEvent(Illusion::Event& e, Collider& c) override;
	bool OnKeyPressed(Illusion::KeyPressedEvent& e) override;
	bool OnMouseButtonPressed(Illusion::MouseButtonPressedEvent& e);
	void OnRender() override;
private:

	bool m_Active = false;

	Illusion::Ref<Illusion::SequenceAnimation> m_Text;

	float m_Time;

};

class Button : public GameObject
{
public:
	Button(std::string passive, std::string active);

	void Init(glm::vec3 pos, glm::vec2 size);

	void OnUpdate();
	void OnRender() override;

	void Active() { m_IsActive = true; }
	void Deactive() { m_IsActive = false; }
private:
	Illusion::Ref<Illusion::Texture2D> m_Passive;
	Illusion::Ref<Illusion::Texture2D> m_Active;

	bool m_IsActive = false;
};

class Bed : public GameObject
{
public: 

	Bed(std::string textpath);

	void OnEvent(Illusion::Event& e, Collider& c) override;
	bool OnKeyPressed(Illusion::KeyPressedEvent& e) override;

private:

	bool m_Time;

};

class Door : public GameObject
{
public:

	Door(std::string textpath, Maps destination, bool trans);

	void OnEvent(Illusion::Event& e, Collider& c) override;
	bool OnKeyPressed(Illusion::KeyPressedEvent& e) override;
	void Door::OnRender() override;

private:

	bool m_IsTransparent;

	Maps m_Destination;
};

class Paint : public GameObject
{
public:

	Paint(std::string textpath);

	void OnRender() override;

	void OnEvent(Illusion::Event& e, Collider& c) override;
	bool OnKeyPressed(Illusion::KeyPressedEvent& e) override;
	bool OnMouseButtonPressed(Illusion::MouseButtonPressedEvent& e);

private:
	Illusion::Ref<Illusion::Texture2D> m_Drawing;

	bool m_Active = false;
};


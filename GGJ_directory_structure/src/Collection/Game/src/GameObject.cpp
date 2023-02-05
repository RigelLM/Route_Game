#include "GameObject.h"


GameObject::GameObject(std::string textpath)
{
	m_Texture.reset(new Illusion::Texture2D(textpath));
}
void GameObject::Init(bool inter, glm::vec3 pos, glm::vec2 size, ColliderInfo& info)
{
	m_Interactable = inter;
	m_Position = pos;
	m_Size = size;
	m_Collider.Init(info);
}
void GameObject::LoadAssets()
{
	m_Notice.reset(new Illusion::Texture2D("assets/textures/utils/Notice.png"));
}
void GameObject::OnUpdate(Collider& c)
{
	if (m_Interactable)
	{
		if (std::get<0>(CollisionTest(c)))
			m_Detected = true;
		else
			m_Detected = false;
	}
}
void GameObject::OnRender()
{
	Illusion::Renderer2D::DrawQuad(m_Position, m_Size, m_Texture);

	if (m_Detected)
		Illusion::Renderer2D::DrawQuad(m_Position + glm::vec3(0.8f, 1.2f, 0.1f), { 1.0f * 1.5f, 0.76f * 1.5f }, m_Notice);
}
Collision GameObject::CollisionTest(Collider& c)
{
	return m_Collider.Test(c);
}
void GameObject::OnEvent(Illusion::Event& e, Collider& c)
{
	if (std::get<0>(CollisionTest(c)))
	{
		Illusion::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Illusion::KeyPressedEvent>(ENGINE_BIND_EVENT_FN(GameObject::OnKeyPressed));
	}
}
bool GameObject::OnKeyPressed(Illusion::KeyPressedEvent& e)
{
	return false;
}

NPC::NPC(std::string path, std::string text, int frame, float time, std::string name)
	:GameObject(path), m_Time(time)
{
	m_Text.reset(new Illusion::SequenceAnimation(frame, text, name));
}
void NPC::OnEvent(Illusion::Event& e, Collider& c)
{
	Illusion::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Illusion::MouseButtonPressedEvent>(ENGINE_BIND_EVENT_FN(NPC::OnMouseButtonPressed));
	if (std::get<0>(CollisionTest(c)))
	{
		dispatcher.Dispatch<Illusion::KeyPressedEvent>(ENGINE_BIND_EVENT_FN(NPC::OnKeyPressed));
	}
}
bool NPC::OnKeyPressed(Illusion::KeyPressedEvent& e)
{
	if (e.GetKeyCode() == ILLUSION_KEY_E)
	{
		m_Active = !m_Active;
		return false;
	}
}
bool NPC::OnMouseButtonPressed(Illusion::MouseButtonPressedEvent& e)
{
	if (m_Active == true)
		m_Active = !m_Active;
	return false;

}
void NPC::OnRender()
{
	Illusion::Renderer2D::DrawQuad(m_Position, glm::vec2(2.3f, 5.3f), m_Texture);

	if (m_Active)
		m_Text->Play(glm::vec3(0.0f, -0.75f, -0.5f), glm::vec2(0.25f* 7.0f, 0.5f * 2.0f), m_Time);

	if (m_Detected)
		Illusion::Renderer2D::DrawQuad(m_Position + glm::vec3(0.8f, 1.2f, 0.1f), { 1.0f * 1.5f, 0.76f * 1.5f }, m_Notice);

}


Button::Button(std::string passive, std::string active)
	:GameObject(passive)
{
	m_Passive.reset(new Illusion::Texture2D(passive));
	m_Active.reset(new Illusion::Texture2D(active));
}
void Button::Init(glm::vec3 pos, glm::vec2 size)
{
	m_Position = pos;
	m_Size = size;
}
void Button::OnUpdate()
{
	if (m_IsActive)
		m_Texture = m_Active;
	else
		m_Texture = m_Passive;
}
void Button::OnRender()
{
	Illusion::Renderer2D::DrawUIQuad(m_Position, m_Size, m_Texture);
}


Bed::Bed(std::string textpath)
	:GameObject(textpath), m_Time(true)
{

}
void Bed::OnEvent(Illusion::Event& e, Collider& c)
{
	if (std::get<0>(CollisionTest(c)))
	{
		Illusion::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Illusion::KeyPressedEvent>(ENGINE_BIND_EVENT_FN(Bed::OnKeyPressed));
	}
}
bool Bed::OnKeyPressed(Illusion::KeyPressedEvent& e)
{
	if (e.GetKeyCode() == ILLUSION_KEY_E)
	{
		m_Time = !m_Time;

		if (m_Time == true)
			GameTime = day;
		else
			GameTime = night;

		return false;
	}
}

Door::Door(std::string textpath, Maps destination, bool trans)
	:GameObject(textpath), m_Destination(destination), m_IsTransparent(trans)
{

}
void Door::OnEvent(Illusion::Event& e, Collider& c)
{
	if (std::get<0>(CollisionTest(c)))
	{
		Illusion::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Illusion::KeyPressedEvent>(ENGINE_BIND_EVENT_FN(Door::OnKeyPressed));
	}
}
bool Door::OnKeyPressed(Illusion::KeyPressedEvent& e)
{
	if (e.GetKeyCode() == ILLUSION_KEY_E)
	{
		MapState = m_Destination;
		return false;
	}
}
void Door::OnRender()
{
	if (!m_IsTransparent)
		Illusion::Renderer2D::DrawQuad(m_Position, m_Size, m_Texture);

	if (m_Detected)
		Illusion::Renderer2D::DrawQuad(m_Position + glm::vec3(0.8f, 1.2f, 0.1f), { 1.0f * 1.5f, 0.76f * 1.5f }, m_Notice);
}

Paint::Paint(std::string textpath)
	:GameObject(textpath)
{
	m_Drawing.reset(new Illusion::Texture2D("assets/textures/drawings/Docter.png"));
}
void Paint::OnEvent(Illusion::Event& e, Collider& c)
{
	Illusion::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Illusion::MouseButtonPressedEvent>(ENGINE_BIND_EVENT_FN(Paint::OnMouseButtonPressed));
	if (std::get<0>(CollisionTest(c)))
	{
		dispatcher.Dispatch<Illusion::KeyPressedEvent>(ENGINE_BIND_EVENT_FN(Paint::OnKeyPressed));
	}
}
bool Paint::OnKeyPressed(Illusion::KeyPressedEvent& e)
{
	if (e.GetKeyCode() == ILLUSION_KEY_E)
	{
		m_Active = !m_Active;
		return false;
	}
}
bool Paint::OnMouseButtonPressed(Illusion::MouseButtonPressedEvent& e)
{
	if (m_Active == true)
		m_Active = !m_Active;
	return false;

}
void Paint::OnRender()
{
	Illusion::Renderer2D::DrawQuad(m_Position, m_Size, m_Texture);

	if (m_Active)
		Illusion::Renderer2D::DrawUIQuad(glm::vec3(0.0f, 0.0f, -0.5f), { 0.75f * 0.9f, 0.75f * 2.0f }, m_Drawing);

	if (m_Detected)
		Illusion::Renderer2D::DrawQuad(m_Position + glm::vec3(0.8f, 1.2f, 0.1f), { 1.0f * 1.5f, 0.76f * 1.5f }, m_Notice);

}
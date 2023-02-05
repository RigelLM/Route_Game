#include "UI.h"


void UI::Init()
{
	m_Base.reset(new Illusion::Texture2D("assets/textures/cover/base.png"));
	m_StartButton.reset(new Button("assets/textures/cover/start1.png", "assets/textures/cover/start2.png"));
	m_QuitButton.reset(new Button("assets/textures/cover/quit1.png", "assets/textures/cover/quit2.png"));
	m_StartButton->Init(glm::vec3(-0.5f, -0.5f, -0.3f), glm::vec2(0.25 * 2.52f, 0.25 * 1.06f));
	m_QuitButton->Init(glm::vec3(0.5f, -0.5f, -0.3f), glm::vec2(0.25 * 2.52f, 0.25 * 1.06f));
}

void UI::OnUpdate(Illusion::Timestep ts)
{
	if (m_CurrentButton)
	{
		m_StartButton->Active();
		m_QuitButton->Deactive();
	}
	else
	{
		m_StartButton->Deactive();
		m_QuitButton->Active();
	}

	m_StartButton->OnUpdate();
	m_QuitButton->OnUpdate();
}

void UI::OnEvent(Illusion::Event& e)
{
	Illusion::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Illusion::KeyPressedEvent>(ENGINE_BIND_EVENT_FN(UI::OnKeyPressed));
}

bool UI::OnKeyPressed(Illusion::KeyPressedEvent& e)
{
	if (e.GetKeyCode() == ILLUSION_KEY_ENTER)
	{
		if (m_CurrentButton)
			State = Play;
		else
			State = GameOver;
	}
	else if (e.GetKeyCode() == ILLUSION_KEY_LEFT)
		m_CurrentButton = true;
	else if (e.GetKeyCode() == ILLUSION_KEY_RIGHT)
		m_CurrentButton = false;

	return false;
}

void UI::OnRender()
{
	Illusion::Renderer2D::DrawUIQuad(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-2.0f,2.0f), m_Base);
	m_StartButton->OnRender();
	m_QuitButton->OnRender();
}
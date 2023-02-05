#include "GameLayer.h"

#include "Engine/Core/Utils/Random.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GameLayer::GameLayer()
	:Layer("GameLayer")
{
	auto& window = Illusion::Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Illusion::Random::Init();
}

void GameLayer::OnAttach()
{
	m_UI.Init();
	m_Level.Init();
	ENGINE_CLIENT_WARN("-----------------All Resources Loaded!-----------------");
}

void GameLayer::OnDetach()
{

}

void GameLayer::OnUpdate(Illusion::Timestep ts)
{
	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });

	switch (State)
	{
		case GameState::GameOver:
		{
			exit(1);
			break;
		}
		case GameState::MainMenu:
		{
			m_UI.OnUpdate(ts);
			break;
		}
		case GameState::Play:
		{
			m_Level.OnUpdate(ts);

			break;
		}
	}
	// Render
	Illusion::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0 });
	Illusion::Renderer2D::BeginScene(*m_Camera);

	switch (State)
	{
	case GameState::MainMenu:
	{
		m_UI.OnRender();
		break;
	}
	case GameState::Play:
	{
		m_Level.OnRender();
		break;
	}
	}

	Illusion::Renderer2D::EndScene();
}

void GameLayer::OnEvent(Illusion::Event& event)
{
	m_Level.OnEvent(event);

	Illusion::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Illusion::WindowResizeEvent>(ENGINE_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<Illusion::KeyPressedEvent>(ENGINE_BIND_EVENT_FN(GameLayer::OnKeyPressed));
}

bool GameLayer::OnKeyPressed(Illusion::KeyPressedEvent& e)
{
	m_UI.OnEvent(e);
	return false;
}

bool GameLayer::OnWindowResize(Illusion::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = Illusion::CreateScope<Illusion::Camera>(left, right, bottom, top);
}

void GameLayer::OnImGuiRender()
{
}
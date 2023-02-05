#pragma once

#include <Engine.h>

#include "Level.h"
#include "UI.h"
#include "GameCore.h"

class GameLayer : public Illusion::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Illusion::Timestep timestep) override;
	void OnEvent(Illusion::Event& event) override;

	void OnImGuiRender() override;

	bool OnKeyPressed(Illusion::KeyPressedEvent& e);
	bool OnWindowResize(Illusion::WindowResizeEvent& e);

private:
	void CreateCamera(uint32_t width, uint32_t height);

private:
	Illusion::Scope<Illusion::Camera> m_Camera;

	Level m_Level;
	UI m_UI;

	float m_Time = 0.0f;
	bool m_Blink = false;

};


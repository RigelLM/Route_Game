#pragma once

#include <Engine.h>

#include "Level.h"
#include "GameObject.h"
#include "GameCore.h"

class UI
{
public:
	void Init();

	void OnUpdate(Illusion::Timestep ts);
	void OnEvent(Illusion::Event& e);
	void OnRender();

	bool OnKeyPressed(Illusion::KeyPressedEvent& e);

private:

	Illusion::Ref<Illusion::Texture2D> m_Base;

	Illusion::Ref<Button> m_StartButton;
	Illusion::Ref<Button> m_QuitButton;

	bool m_CurrentButton = false;

};


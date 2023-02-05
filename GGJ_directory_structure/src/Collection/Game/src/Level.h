#pragma once

#include "Player.h"
#include "GameObject.h"
#include "Map.h"

#include "Engine/Sound/Soundplayer.h"

class Level
{
public:
	void Init();

	void OnUpdate(Illusion::Timestep ts);
	void OnEvent(Illusion::Event& e);
	void OnRender();

	bool IsGameOver() const { return m_GameOver; }

	Player& GetPlayer() { return m_Player; }

private:

	void GameOver();
private:

	Player m_Player;

	std::unordered_map<std::string, Illusion::Ref<Map>> m_Maps;

	bool m_GameOver = false;

	Illusion::Ref<Illusion::SoundPlayer> m_BGMPlayer;
};
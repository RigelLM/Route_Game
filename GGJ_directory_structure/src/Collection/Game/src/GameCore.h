#pragma once

enum Maps
{
	None, town, hotel_room, docter_room, townhall_room
};

enum Time
{
	day, night
};

enum GameState
{
	Play, MainMenu, GameOver
};

extern GameState State;

extern Maps MapState;

extern Maps LastMap;

extern Time GameTime;
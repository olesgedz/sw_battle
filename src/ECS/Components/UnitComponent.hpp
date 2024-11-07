#pragma once

struct GameID
{
	static int nextId;
};


struct UnitComponent : public GameID{
	int gameId;
	int spawnOrder;
	 UnitComponent(int gameId = 0, int spawnOrder = 0) : gameId(gameId), spawnOrder(spawnOrder) {
	}
};
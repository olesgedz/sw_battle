#pragma once

struct GameID
{
	static uint32_t nextId;
};


struct UnitComponent : public GameID{
	uint32_t gameId;
	uint32_t spawnOrder;
	 UnitComponent(uint32_t gameId = 0, uint32_t spawnOrder = 0) : gameId(gameId), spawnOrder(spawnOrder) {
	}
};
#pragma once
#include <cstdint>
struct AgilityComponent {
	uint32_t agility;


	explicit AgilityComponent(uint32_t  agility = 0) :
	  agility(agility) {
	}
};
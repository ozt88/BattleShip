#pragma once
#include "Include.h"
class Ship;
class GameManager
{
public:
	GameManager();
	~GameManager();
	
	void Render();

private:
	std::vector<Ship*> m_ShipList;
};


#pragma once
#include "stdafx.h"
#include "Enums.h"

class GameManager;

class Engine
{
public:
	Engine();
	~Engine();
	void EngineStart();
	Menu StartMenu();
private:
	GameManager* m_GM;
};


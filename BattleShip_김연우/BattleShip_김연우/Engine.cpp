#include "stdafx.h"
#include "Engine.h"
#include "GameManager.h"

Engine::Engine()
{
	m_GM = new GameManager;
}


Engine::~Engine()
{
	delete m_GM;
}

void Engine::EngineStart()
{
	Menu menuInput = MENU_NONE;
	srand( (unsigned) time( NULL ) );
	while( 1 )
	{
		system("cls");
		menuInput = StartMenu();
		switch( menuInput )
		{
			case MENU_NONE:
				break;
			case GAMESTART:
				m_GM->GameStart();
				break;
			case GAMEQUIT:
				return;
		}
	}
}

Menu Engine::StartMenu()
{
	int menuInput = 0;
	std::cout << "\n\t<<<<<<BATTLE SHIP>>>>>>\n\n";
	std::cout << "\n\t[1].Game Start\n\n";
	std::cout << "\n\t[2].Quit Game\n\n";
	std::cout << "\n\t>>";
	fflush( stdin );
	std::cin >> menuInput;
	return ( Menu )menuInput;
}

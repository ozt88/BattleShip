#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"                                            


GameManager::GameManager()
	:m_NumOfTurn(0)
{
	m_Attacker = new Player;
	m_Attacker->SetName( "Attacker" );
	m_Defender = new Player;
	m_Defender->SetName( "Defender" );
}


GameManager::~GameManager()
{
	delete m_Attacker;
	delete m_Defender;
}

void GameManager::InitGame()
{
	system( "cls" );
	m_NumOfTurn = 0;
	printf_s( "Let the game begin\n" );
	m_Attacker->InitPlayer();
	m_Defender->InitPlayer();
}

void GameManager::Update()
{
	printf( "---------------TURN %d---------------\n" , ++m_NumOfTurn );
	Position hitPosition = m_Attacker->Attack();
	HitResult hitResult = m_Defender->SendResult( hitPosition );
	m_Attacker->UpdateEnemyBoard( hitPosition , hitResult );
	m_Defender->UpdateMyBoard( hitPosition , hitResult );
	
	Position hitPosition2 = m_Defender->Attack();
	HitResult hitResult2 = m_Attacker->SendResult( hitPosition2 );
	m_Defender->UpdateEnemyBoard( hitPosition2 , hitResult2 );
	m_Attacker->UpdateMyBoard( hitPosition2 , hitResult2 );
	//check process
	PrintResult( hitResult );
	PrintResult( hitResult2 );

	//m_Defender->GetMyBoard();
	//m_Defender->PrintShips();
}

void GameManager::PrintResult( HitResult hitResult )
{
	switch( hitResult )
	{
		case WATER:
			printf_s( "Result Error\n" );
			break;
		case HIT:
			printf_s( "Hit!\n" );
			break;
		case MISS:
			printf_s( "Missed.\n" );
			break;
		case DESTROY:
			printf_s( "Destroyed.\n" );
			break;
		case DESTROY_AIRCRAFT:
			printf_s( "Aircraft Destroyed.\n" );
			break;
		case DESTROY_BATTLESHIP:
			printf_s( "BattleShip Destroyed.\n" );
			break;
		case DESTROY_CRUISER:
			printf_s( "Cruiser Destroyed.\n" );
			break;
		case DESTROY_DESTROYER:
			printf_s( "Destroyer Destroyed.\n" );
			break;
		default:
			break;
	}
}

void GameManager::GameStart()
{
	InitGame();
	while( !m_Defender->AllShipIsDestroyed() ||
		   !m_Attacker->AllShipIsDestroyed()
		 )
	{
		Update();
	}
	printf_s( "In %d ,GAME Over\n" , m_NumOfTurn );
}

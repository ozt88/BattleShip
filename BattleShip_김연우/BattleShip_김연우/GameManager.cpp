#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "AirCraft.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"                                                       

static int numOfTurn;

GameManager::GameManager()
{
	m_Attacker = new Player;
	m_Defender = new Player;
}


GameManager::~GameManager()
{
	delete m_Attacker;
	delete m_Defender;
}

void GameManager::InitGame()
{
	numOfTurn = 0;
	printf_s( "Let the game begin\n" );
	m_Attacker->SetupShips();
	m_Defender->SetupShips();
}

void GameManager::Update()
{
	printf( "---------------TURN %d---------------\n" , ++numOfTurn );
	Position hitPosition = m_Attacker->Attack();
	HitResult hitResult = m_Defender->SendResult( hitPosition );
	m_Attacker->SetEnemyBoard( hitPosition , hitResult );
	m_Defender->SetMyBoard( hitPosition , hitResult );

	//check process
	PrintResult( hitResult );
	m_Defender->GetMyBoard();
	m_Defender->PrintShips();
}

void GameManager::PrintResult( HitResult hitResult )
{
	switch( hitResult )
	{
		case NONE:
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
	while( 1 )
	{
		Update();
		if( m_Defender->AllShipIsDestroyed() )
		{
			printf_s( "%s is Over\n" , m_Defender->getName().c_str() );
			break;
		}
	}
}

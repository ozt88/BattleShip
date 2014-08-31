#include "GameManager.h"
#include "Ship.h"

GameManager::GameManager()
{
	Ship* ship1 = new Ship();
	ship1->SetPosX( 100 );
	Ship* ship2 = new Ship();
	ship2->SetPosX( 200 );
	m_ShipList.push_back(ship1);
	m_ShipList.push_back(ship2);

}


GameManager::~GameManager()
{
}

void GameManager::Render()
{
	for( auto ship : m_ShipList )
	{
		ship->Render();
	}
}

#include "BattleShip.h"


BattleShip::BattleShip()
{
	m_HorizontalBitmap = new Bitmap( L"Resource/BattleShipH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/BattleShipV.png" );
	m_BattleSprite->Width( 4 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 4;
	m_HP = m_MaxHP;
	m_Type = BATTLESHIP;
	m_Name = "BattleShip";
}

BattleShip::BattleShip( float rowNum )
{
	m_HorizontalBitmap = new Bitmap( L"Resource/BattleShipH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/BattleShipV.png" );
	m_BattleSprite->Width( 4 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 4;
	m_HP = m_MaxHP;
	m_Type = BATTLESHIP;
	m_Name = "BattleShip";
	m_UISprite->Create( m_HorizontalBitmap , ( float )m_MaxHP , rowNum );
}



BattleShip::~BattleShip()
{
	m_HorizontalBitmap->Release();
	m_VerticalBitmap->Release();
}

HitResult BattleShip::HitCheck( Position hitPos )
{
	HitResult result = Ship::HitCheck( hitPos );
	return ( result == DESTROY ) ? DESTROY_BATTLESHIP : result;
}

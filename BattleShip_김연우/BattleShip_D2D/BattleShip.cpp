#include "BattleShip.h"


BattleShip::BattleShip()
{
	m_HorizontalBitmap = new Bitmap( L"Resource/BattleShipH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/BattleShipV.png" );
	m_DestroyedBitmap = new Bitmap( L"Resource/BattleShipD.png" );
	m_BattleSprite->Width( 4 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 4;
	m_HP = m_MaxHP;
	m_Type = BATTLESHIP;
	m_Name = "BattleShip";
	m_BattleSprite->SetObject( 0.f , 0.f , ( float )m_MaxHP , 1.f );
	m_EnemyUISprite->SetObject( 0.f , 0.f , ( float )m_MaxHP , 0.5f );
	m_EnemyUISprite->SetNormalBitmap( m_HorizontalBitmap );
	m_EnemyUISprite->SetDestroyedBitmap( m_DestroyedBitmap );
}

BattleShip::BattleShip( float rowNum )
{
	m_HorizontalBitmap = new Bitmap( L"Resource/BattleShipH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/BattleShipV.png" );
	m_DestroyedBitmap = new Bitmap( L"Resource/BattleShipD.png" );
	m_BattleSprite->Width( 4 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 4;
	m_HP = m_MaxHP;
	m_Type = BATTLESHIP;
	m_Name = "BattleShip";
	m_BattleSprite->SetObject( 0.f , 0.f , ( float )m_MaxHP , 1.f );
	m_EnemyUISprite->SetObject( 0.f , rowNum , ( float )m_MaxHP , 0.5f );
	m_UISprite->Create( m_HorizontalBitmap , m_DestroyedBitmap, ( float )m_MaxHP , rowNum );
	m_EnemyUISprite->SetNormalBitmap( m_HorizontalBitmap );
	m_EnemyUISprite->SetDestroyedBitmap( m_DestroyedBitmap );
}



BattleShip::~BattleShip()
{

}

HitResult BattleShip::HitCheck( Position hitPos )
{
	HitResult result = Ship::HitCheck( hitPos );
	return ( result == DESTROY ) ? DESTROY_BATTLESHIP : result;
}

#include "AirCraft.h"

AirCraft::AirCraft()
{
	m_HorizontalBitmap = new Bitmap( L"Resource/AirCraftH.png");
	m_VerticalBitmap = new Bitmap( L"Resource/AirCraftV.png" );
	m_DestroyedBitmap = new Bitmap( L"Resource/AirCraftD.png" );

	m_MaxHP = 5;
	m_HP = m_MaxHP;
	m_Type = AIRCRAFT;
	m_Name = "AirCraft";
	m_BattleSprite->SetObject( 0.f , 0.f , ( float )m_MaxHP , 1.f );
	m_EnemyUISprite->SetObject( 0.f , 0.f , ( float )m_MaxHP , 0.5f );
	m_EnemyUISprite->SetNormalBitmap( m_HorizontalBitmap );
	m_EnemyUISprite->SetDestroyedBitmap( m_DestroyedBitmap );
}

AirCraft::AirCraft( float rowNum )
{
	m_HorizontalBitmap = new Bitmap( L"Resource/AirCraftH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/AirCraftV.png" );
	m_DestroyedBitmap = new Bitmap( L"Resource/AirCraftD.png" );
	m_MaxHP = 5;
	m_HP = m_MaxHP;
	m_Type = AIRCRAFT;
	m_Name = "AirCraft";
	m_BattleSprite->SetObject( 0.f , 0.f , ( float )m_MaxHP , 1.f );
	m_EnemyUISprite->SetObject( 0.f , rowNum , ( float )m_MaxHP , 0.5f );
	m_UISprite->Create( m_HorizontalBitmap , m_DestroyedBitmap, ( float )m_MaxHP , rowNum );
	m_EnemyUISprite->SetNormalBitmap( m_HorizontalBitmap );
	m_EnemyUISprite->SetDestroyedBitmap( m_DestroyedBitmap );
}



AirCraft::~AirCraft()
{

}

HitResult AirCraft::HitCheck( Position hitPos )
{
	HitResult result = Ship::HitCheck( hitPos );
	return ( result == DESTROY ) ? DESTROY_AIRCRAFT : result;
}

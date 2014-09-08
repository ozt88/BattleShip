#include "AirCraft.h"

AirCraft::AirCraft()
{
	m_HorizontalBitmap = new Bitmap( L"Resource/AirCraftH.png");
	m_VerticalBitmap = new Bitmap( L"Resource/AirCraftV.png" );
	m_BattleSprite->Width( 5 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 5;
	m_HP = m_MaxHP;
	m_Type = AIRCRAFT;
	m_Name = "AirCraft";
}

AirCraft::AirCraft( float rowNum )
{
	m_HorizontalBitmap = new Bitmap( L"Resource/AirCraftH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/AirCraftV.png" );
	m_BattleSprite->Width( 5 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 5;
	m_HP = m_MaxHP;
	m_Type = AIRCRAFT;
	m_Name = "AirCraft";
	m_UISprite->Create( m_HorizontalBitmap , ( float )m_MaxHP , rowNum );
}



AirCraft::~AirCraft()
{
	m_VerticalBitmap->Release();
	m_HorizontalBitmap->Release();
}

HitResult AirCraft::HitCheck( Position hitPos )
{
	HitResult result = Ship::HitCheck( hitPos );
	return ( result == DESTROY ) ? DESTROY_AIRCRAFT : result;
}

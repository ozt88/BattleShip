#include "Cruiser.h"


Cruiser::Cruiser()
{
	m_HorizontalBitmap = new Bitmap( L"Resource/CruiserH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/CruiserV.png" );
	m_BattleSprite->Width( 3 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 3;
	m_HP = m_MaxHP;
	m_Type = CRUISER;
	m_Name = "Cruiser";
}

Cruiser::Cruiser( float rowNum )
{
	m_HorizontalBitmap = new Bitmap( L"Resource/CruiserH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/CruiserV.png" );
	m_BattleSprite->Width( 3 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 3;
	m_HP = m_MaxHP;
	m_Type = CRUISER;
	m_Name = "Cruiser";
	m_UISprite->Create( m_HorizontalBitmap , ( float )m_MaxHP , rowNum );
}



Cruiser::~Cruiser()
{
	m_HorizontalBitmap->Release();
	m_VerticalBitmap->Release();
}

HitResult Cruiser::HitCheck( Position hitPos )
{
	HitResult result = Ship::HitCheck( hitPos );
	return ( result == DESTROY ) ? DESTROY_CRUISER : result;
}
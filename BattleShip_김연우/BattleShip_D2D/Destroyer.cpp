#include "Destroyer.h"


Destroyer::Destroyer()
{
	m_HorizontalBitmap = new Bitmap( L"Resource/DestroyerH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/DestroyerV.png" );
	m_BattleSprite->Width( 2 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 2;
	m_HP = m_MaxHP;
	m_Type = DESTROYER;
	m_Name = "Destroyer";
}

Destroyer::Destroyer( float rowNum )
{
	m_HorizontalBitmap = new Bitmap( L"Resource/DestroyerH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/DestroyerV.png" );
	m_BattleSprite->Width( 2 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 2;
	m_HP = m_MaxHP;
	m_Type = DESTROYER;
	m_Name = "Destroyer";
	m_UISprite->Create( m_HorizontalBitmap , ( float )m_MaxHP , rowNum );
}



Destroyer::~Destroyer()
{
	m_HorizontalBitmap->Release();
	m_VerticalBitmap->Release();
}

HitResult Destroyer::HitCheck( Position hitPos )
{
	HitResult result = Ship::HitCheck( hitPos );
	return ( result == DESTROY ) ? DESTROY_DESTROYER : result;
}
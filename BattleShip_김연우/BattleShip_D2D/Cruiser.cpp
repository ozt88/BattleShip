#include "Cruiser.h"


Cruiser::Cruiser()
{
	m_HorizontalBitmap = new Bitmap( L"Resource/CruiserH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/CruiserV.png" );
	m_DestroyedBitmap = new Bitmap( L"Resource/CruiserD.png" );

	m_BattleSprite->Width( 3 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 3;
	m_HP = m_MaxHP;
	m_Type = CRUISER;
	m_Name = "Cruiser";
	m_BattleSprite->SetObject( 0.f , 0.f , ( float )m_MaxHP , 1.f );
	m_EnemyUISprite->SetObject( 0.f , 0.f , ( float )m_MaxHP , 0.5f );
	m_EnemyUISprite->SetNormalBitmap( m_HorizontalBitmap );
	m_EnemyUISprite->SetDestroyedBitmap( m_DestroyedBitmap );
}

Cruiser::Cruiser( float rowNum )
{
	m_HorizontalBitmap = new Bitmap( L"Resource/CruiserH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/CruiserV.png" );
	m_DestroyedBitmap = new Bitmap( L"Resource/CruiserD.png" );

	m_BattleSprite->Width( 3 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 3;
	m_HP = m_MaxHP;
	m_Type = CRUISER;
	m_Name = "Cruiser";
	m_BattleSprite->SetObject( 0.f , 0.f , ( float )m_MaxHP , 1.f );
	m_EnemyUISprite->SetObject( 0.f , rowNum , ( float )m_MaxHP , 0.5f );
	m_UISprite->Create( m_HorizontalBitmap , m_DestroyedBitmap, ( float )m_MaxHP , rowNum );
	m_EnemyUISprite->SetNormalBitmap( m_HorizontalBitmap );
	m_EnemyUISprite->SetDestroyedBitmap( m_DestroyedBitmap );
}



Cruiser::~Cruiser()
{

}

HitResult Cruiser::HitCheck( Position hitPos )
{
	HitResult result = Ship::HitCheck( hitPos );
	return ( result == DESTROY ) ? DESTROY_CRUISER : result;
}
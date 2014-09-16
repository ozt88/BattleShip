#include "Destroyer.h"


Destroyer::Destroyer()
{
	m_HorizontalBitmap = new Bitmap( L"Resource/DestroyerH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/DestroyerV.png" );
	m_DestroyedBitmap = new Bitmap( L"Resource/DestroyerD.png" );

	m_BattleSprite->Width( 2 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 2;
	m_HP = m_MaxHP;
	m_Type = DESTROYER;
	m_Name = "Destroyer";
	m_BattleSprite->SetObject( 0.f , 0.f , (float) m_MaxHP , 1.f );
	m_EnemyUISprite->SetObject( 0.f , 0.f , ( float ) m_MaxHP , 0.5f );
	m_EnemyUISprite->SetNormalBitmap( m_HorizontalBitmap );
	m_EnemyUISprite->SetDestroyedBitmap( m_DestroyedBitmap );
}

Destroyer::Destroyer( float rowNum )
{
	m_HorizontalBitmap = new Bitmap( L"Resource/DestroyerH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/DestroyerV.png" );
	m_DestroyedBitmap = new Bitmap( L"Resource/DestroyerD.png" );

	m_BattleSprite->Width( 2 );
	m_BattleSprite->Height( 1 );
	m_MaxHP = 2;
	m_HP = m_MaxHP;
	m_Type = DESTROYER;
	m_Name = "Destroyer";
	m_BattleSprite->SetObject( 0.f , 0.f , ( float )m_MaxHP , 1.f );
	m_EnemyUISprite->SetObject( 0.f , rowNum , ( float )m_MaxHP , 0.5f );
	m_UISprite->Create( m_HorizontalBitmap , m_DestroyedBitmap, ( float )m_MaxHP , rowNum );
	m_EnemyUISprite->SetNormalBitmap( m_HorizontalBitmap );
	m_EnemyUISprite->SetDestroyedBitmap( m_DestroyedBitmap );
}



Destroyer::~Destroyer()
{

}

HitResult Destroyer::HitCheck( Position hitPos )
{
	HitResult result = Ship::HitCheck( hitPos );
	return ( result == DESTROY ) ? DESTROY_DESTROYER : result;
}
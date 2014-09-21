#include "AirCraft.h"


AirCraft::AirCraft()
{
	//쉽이 가진 세가지 스프라이트들에 들어가는 비트맵이 쉽 타입별로 다르기 때문에
	//하부 클래스인 ABCD의 생성자별로 각각 알맞은 비트맵을 생성한다.
	m_HorizontalBitmap = new Bitmap( L"Resource/AirCraftH.png");
	m_VerticalBitmap = new Bitmap( L"Resource/AirCraftV.png" );
	m_DestroyedBitmap = new Bitmap( L"Resource/AirCraftD.png" );

	//배의 속성정보들도 배의 타입별로 나누어 값을 설정한다.
	m_MaxHP = ShipSize::AIRCRAFT_SIZE;
	m_HP = m_MaxHP;
	m_Type = AIRCRAFT;
	m_Name = "AirCraft";
	m_BattleSprite->SetObject( 0.f , 0.f , ( float )m_MaxHP , 1.f );
	m_EnemyUISprite->SetObject( 0.f , 0.f , ( float )m_MaxHP , 0.5f );
	m_EnemyUISprite->SetNormalBitmap( m_HorizontalBitmap );
	m_EnemyUISprite->SetDestroyedBitmap( m_DestroyedBitmap );
}

//rowNum을 인자로 받는 이 생성자는 
//UI와 EnemyUI에 들어가는 스프라이트들의 posY값을 순서대로 넣기 위하여 만들어졌다.
//순서대로 배치시키게 하기 위해서 만들어 졌다.

//##UI를 위해 rowNum을 직접 입력하는 생성자가 가독성이 떨어지는 것같다. 
//##차후 수정필요

AirCraft::AirCraft( float rowNum )
{
	m_HorizontalBitmap = new Bitmap( L"Resource/AirCraftH.png" );
	m_VerticalBitmap = new Bitmap( L"Resource/AirCraftV.png" );
	m_DestroyedBitmap = new Bitmap( L"Resource/AirCraftD.png" );
	m_MaxHP = ShipSize::AIRCRAFT_SIZE;
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

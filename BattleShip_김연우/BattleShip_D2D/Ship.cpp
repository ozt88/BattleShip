#include "Include.h"
#include "Ship.h"

Ship::Ship()
	:m_Pos() , m_Name() , m_MaxHP(0) , m_HP(0) , 
	m_HorizontalBitmap(nullptr) , m_VerticalBitmap(nullptr) , m_DestroyedBitmap(nullptr)
{
	m_BattleSprite = new D2DSprite();
	m_EnemyUISprite = new ActiveShipSprite();
	m_UISprite = new UIShipObject();
}

Ship::~Ship()
{
	//safeRelesase
	m_HorizontalBitmap->SafeRelease();
	m_VerticalBitmap->SafeRelease();
	m_DestroyedBitmap->SafeRelease();

	m_BattleSprite->Clear();
	m_UISprite->Clear();
	m_EnemyUISprite->Clear();
}

void Ship::ShipInit()
{
	m_Pos.clear();
	m_UISprite->Init();
	SetHP( m_MaxHP );
	m_IsDestroyed = false;
}

//setPos를 시작으로 direction 방향으로 배를 배치(Pos에 위치값 추가)
void Ship::PlaceShip( Position setPos , MyDirection direction )
{
	Position curPos = setPos;
	for( int i = 0; i < GetMaxHP(); i++ )
	{
		AddPosition( curPos );
		curPos = curPos.dirPos( direction );
	}
	
	//그후 BattleSprite의 위치를 정해주고 종/횡 비트맵 설정
	//배틀쉽 게임내에서 스프라이트의 위치가 변화할 경우가 없으므로
	//초기화할때 사용되는 PlaceShip에서만 지정하면 된다.

	switch( direction )
	{
		case UP:
			m_BattleSprite->SetObject( ( float )m_Pos.back().m_X , ( float )m_Pos.back().m_Y ,
									   ( float )1 , ( float )m_MaxHP );
			m_BattleSprite->SetBitmap( m_VerticalBitmap );
			break;
		case DOWN:
			m_BattleSprite->SetObject( ( float )m_Pos.front().m_X , ( float )m_Pos.front().m_Y ,
									   ( float )1 , ( float )m_MaxHP );
			m_BattleSprite->SetBitmap( m_VerticalBitmap );
			break;
		case LEFT:
			m_BattleSprite->SetObject( ( float )m_Pos.back().m_X , ( float )m_Pos.back().m_Y ,
									   ( float )m_MaxHP , ( float )1 );
			m_BattleSprite->SetBitmap( m_HorizontalBitmap );
			break;
		case RIGHT:
			m_BattleSprite->SetObject( ( float )m_Pos.front().m_X , ( float )m_Pos.front().m_Y ,
									   ( float )m_MaxHP , ( float )1 );
			m_BattleSprite->SetBitmap( m_HorizontalBitmap );
			break;
		default:
			break;
	}
}


void Ship::AddPosition( Position addPos )
{
	for( auto positionIter : m_Pos )
	{
		if( positionIter.m_X == addPos.m_X && positionIter.m_Y == addPos.m_Y )
		{
			printf_s( "ERROR : Already Exist\n" );
			return;
		}
	}

	m_Pos.push_back( addPos );
}


HitResult Ship::HitCheck( Position hitPos )
{

	for( auto positionIter : m_Pos )
	{
		if( positionIter.m_X == hitPos.m_X && positionIter.m_Y == hitPos.m_Y )
		{
			positionIter.m_X = -1;
			positionIter.m_Y = -1;
			--m_HP;
			//Hp가 깎인 것을 UIsprite에도 전달.
			//HP Sprite 하나를 줄여줌
			m_UISprite->Hit();

			if( m_HP <= 0 )
			{
				m_IsDestroyed = true;
				//파괴된 경우 UISprite의 ShipSprite를 파괴비트맵으로 전환
				m_UISprite->GetShipSprite()->SetDestroy( true );
				return DESTROY;
			}
			else
			{
				return HIT;
			}
		}
	}

	return MISS;
}

//배를 배치할때 겹치면 안된다. 따라서 필요한 Duplicate 체크를 실행하는 함수.
bool Ship::IsDuplicate( Position checkPos )
{

	for( auto positionIter : m_Pos )
	{
		if( positionIter.m_X == checkPos.m_X && positionIter.m_Y == checkPos.m_Y )
		{
			return true;
		}
	}
	return false;
}




void Ship::SetHP( int _hp )
{
	_ASSERTE( _hp < 100 && "HP is Over 100" );

	m_HP = _hp;
}








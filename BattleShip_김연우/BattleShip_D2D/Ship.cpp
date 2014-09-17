#include "Include.h"
#include "Ship.h"

Ship::Ship()
	:m_Pos() , m_Name() , m_MaxHP(0) , m_HP(0) , 
	m_HorizontalBitmap(nullptr) , m_VerticalBitmap(nullptr) , m_DestroyedBitmap(nullptr)
{
	m_BattleSprite = new D2DSprite();
	m_EnemyUISprite = new BFShipSprite();
	m_UISprite = new UIShipObject();
}


Ship::~Ship()
{
	m_HorizontalBitmap->Release();
	m_VerticalBitmap->Release();
	m_DestroyedBitmap->Release();

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

void Ship::PlaceShip( Position setPos , MyDirection direction )
{
	for( int i = 0; i < GetMaxHP(); i++ )
	{
		AddPosition( setPos );

		switch( direction )
		{
			case UP:
				setPos.m_Y--;
				break;
			case DOWN:
				setPos.m_Y++;
				break;
			case LEFT:
				setPos.m_X--;
				break;
			case RIGHT:
				setPos.m_X++;
				break;
		}
	}
	

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
			m_UISprite->Hit();

			if( m_HP <= 0 )
			{
				m_IsDestroyed = true;
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








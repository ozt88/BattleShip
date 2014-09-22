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

//setPos�� �������� direction �������� �踦 ��ġ(Pos�� ��ġ�� �߰�)
void Ship::PlaceShip( Position setPos , MyDirection direction )
{
	Position curPos = setPos;
	for( int i = 0; i < GetMaxHP(); i++ )
	{
		AddPosition( curPos );
		curPos = curPos.dirPos( direction );
	}
	
	//���� BattleSprite�� ��ġ�� �����ְ� ��/Ⱦ ��Ʈ�� ����
	//��Ʋ�� ���ӳ����� ��������Ʈ�� ��ġ�� ��ȭ�� ��찡 �����Ƿ�
	//�ʱ�ȭ�Ҷ� ���Ǵ� PlaceShip������ �����ϸ� �ȴ�.

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
			//Hp�� ���� ���� UIsprite���� ����.
			//HP Sprite �ϳ��� �ٿ���
			m_UISprite->Hit();

			if( m_HP <= 0 )
			{
				m_IsDestroyed = true;
				//�ı��� ��� UISprite�� ShipSprite�� �ı���Ʈ������ ��ȯ
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

//�踦 ��ġ�Ҷ� ��ġ�� �ȵȴ�. ���� �ʿ��� Duplicate üũ�� �����ϴ� �Լ�.
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








#include "EnemyUI.h"
#include "Enum.h"
#include "BFShipSprite.h"

EnemyUI::EnemyUI()
{
}


EnemyUI::~EnemyUI()
{
}

void EnemyUI::Init()
{
	SetObject( POSX , POSY , WIDTH , HEIGTH );
	m_BoxWidth = m_Width / ( SHIP_NUM + 1 );
	m_BoxHeight = m_Height / ( SHIP_NUM + 1 );
	m_ScaleX = m_BoxWidth;
	m_ScaleY = m_BoxHeight;

	for( auto child : m_ChildList )
	{
		child->Init();
	}
}

void EnemyUI::MakeDestroySprite( int size )
{
	for( auto child : m_ChildList )
	{
		if( child->Width() == size )
		{
			((BFShipSprite*)child)->SetDestroy( true );
			break;
		}
	}
}

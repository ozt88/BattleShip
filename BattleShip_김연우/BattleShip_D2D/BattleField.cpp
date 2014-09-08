#include "Include.h"
#include "BattleField.h"


BattleField::BattleField()
	:m_BoxHeight(0.f) , m_BoxWidth(0.f)
{
}


BattleField::~BattleField()
{
	m_Brush->Release();
}

void BattleField::Init()
{
	GetRenderer()->GetHwndRenderTarget()->
		CreateSolidColorBrush
		(D2D1::ColorF( D2D1::ColorF::LightSlateGray ) ,&m_Brush);

	m_Width = WIDTH;
	m_Height = HEIGTH;
	m_PosX = POSX;
	m_PosY = POSY;
	m_BoxWidth = m_Width / MAP_WIDTH;
	m_BoxHeight = m_Height / MAP_HEIGHT;
	m_ScaleX = m_BoxWidth;
	m_ScaleY = m_BoxHeight;
}

void BattleField::Render()
{
	D2DObject::Render();

 	GetRenderer()->GetHwndRenderTarget()->
 		SetTransform( D2D1::Matrix3x2F::Identity() );
	
	for( int i = 0; i < MAP_WIDTH + 1 ; ++i )
	{
		GetRenderer()->GetHwndRenderTarget()->DrawLine(
			D2D1::Point2F( PosX() + ( i * m_BoxWidth ) , PosY() ) ,
			D2D1::Point2F( PosX() + ( i * m_BoxWidth ) , PosY() + Height() ) ,
			m_Brush
			);
	}
	for( int i = 0; i < MAP_HEIGHT+1; ++i )
	{
		GetRenderer()->GetHwndRenderTarget()->DrawLine(
			D2D1::Point2F( PosX() , PosY() + ( i * m_BoxHeight ) ) ,
			D2D1::Point2F( PosX() + Width() , PosY() + ( i * m_BoxHeight ) ) ,
			m_Brush
			);
	}
	
}
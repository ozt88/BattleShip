#include "UIShipObject.h"
#include "Enum.h"

UIShipObject::UIShipObject()
{
	m_Height = 1;
	m_Width = 1;
	m_PosX = 0;
	m_PosY = 0;
	m_HPBitmap = new Bitmap( L"Resource/drum2.png" );
	m_ShipSprite = new D2DSprite();
}


UIShipObject::~UIShipObject()
{
}

void UIShipObject::Create( Bitmap* bitmap , float maxHP, float posY )
{
	this->PosY( posY );
	this->Width( maxHP );
	m_ScaleX = 1;
	m_ScaleY = m_Height;

	m_ShipSprite->SetBitmap( bitmap );
	m_ShipSprite->PosX( 0 );
	m_ShipSprite->PosY( 0 );
	m_ShipSprite->Width( maxHP );
	m_ShipSprite->Height( 0.5 );
	

	D2DSprite* newHPSprite = nullptr;
	for( float i = 0; i < maxHP; ++i )
	{
		newHPSprite = new D2DSprite();
		newHPSprite->SetBitmap( m_HPBitmap );
		newHPSprite->PosX( ( float ) i );
		newHPSprite->PosY( ( float ) 0.6 );
		newHPSprite->Width( ( float ) 0.8 );
		newHPSprite->Height( ( float ) 0.2 );
		m_HPSpriteList.push_back( newHPSprite );
	}
}

void UIShipObject::Hit()
{
	if( m_HPSpriteList.empty() )
	{
		return;
	}
	D2DSprite* deleteSprite = m_HPSpriteList.back();
	this->RemoveChild( deleteSprite , false );
}

void UIShipObject::Init()
{
	AddChild( m_ShipSprite );
	for( auto hpSprite : m_HPSpriteList )
	{
		AddChild( hpSprite );
	}
}


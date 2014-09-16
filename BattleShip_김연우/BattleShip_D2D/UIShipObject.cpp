#include "UIShipObject.h"
#include "Enum.h"

UIShipObject::UIShipObject()
{
	m_Height = 1;
	m_Width = 1;
	m_PosX = 0;
	m_PosY = 0;
	m_HPBitmap = new Bitmap( L"Resource/drum2.png" );
	m_ShipSprite = new BFShipSprite();
}


UIShipObject::~UIShipObject()
{
	m_HPBitmap->Release();
	m_ShipSprite->Clear();
}

void UIShipObject::Create( Bitmap* normalBitmap , Bitmap* destroyedBitmap , float maxHP, float posY )
{
	SetObject( 0 , posY , maxHP , 1 );
	m_ScaleX = 1;
	m_ScaleY = m_Height;

	m_ShipSprite->SetNormalBitmap( normalBitmap );
	m_ShipSprite->SetDestroyedBitmap( destroyedBitmap );
	m_ShipSprite->SetObject( 0 , 0 , maxHP , 0.5 );
	AddChild( m_ShipSprite );
}

void UIShipObject::Hit()
{
	if( m_HPSpriteList.empty() )
	{
		return;
	}
	D2DSprite* deleteSprite = m_HPSpriteList.back();
	m_HPSpriteList.remove( deleteSprite );
	this->RemoveChild( deleteSprite , true );
}

void UIShipObject::Init()
{
	Clear();
	m_ShipSprite->Init();
	D2DSprite* newHPSprite = nullptr;
	for( float i = 0; i < m_ShipSprite->Width(); ++i )
	{
		newHPSprite = new D2DSprite();
		newHPSprite->SetBitmap( m_HPBitmap );
		newHPSprite->SetObject( i , 0.6f , 0.8f , 0.2f );
		m_HPSpriteList.push_back( newHPSprite );
	}
	for( auto hpSprite : m_HPSpriteList )
	{
		AddChild( hpSprite );
	}
}

void UIShipObject::Clear()
{

	if( !m_HPSpriteList.empty() )
	{
		for( auto sprite : m_HPSpriteList )
		{
			if( sprite )
			{
				RemoveChild( sprite , false );
				SafeDelete( sprite );
			}
		}
		m_HPSpriteList.clear();
	}
}


#include "Ship.h"
#include "D2DSprite.h"

Ship::Ship()
	:m_PosX(0.f) , m_PosY(0.f)
{
	m_Sprite = new D2DSprite( L"Resource/ship.png" );
}


Ship::~Ship()
{
	m_Sprite->Clear();
}

void Ship::Render()
{
	m_Sprite->Render();
}

void Ship::SetPosX( float val )
{
	m_Sprite->PosX( val );
	m_PosX = val;
}

void Ship::SetPosY( float val )
{
	m_Sprite->PosY( val );
	m_PosY = val;
}

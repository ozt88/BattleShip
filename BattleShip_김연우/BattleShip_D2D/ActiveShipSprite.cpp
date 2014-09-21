#include "ActiveShipSprite.h"

ActiveShipSprite::ActiveShipSprite()
	:m_IsDestroyed(false) , m_NormalBitmap(nullptr) , m_DestroyedBitmap(nullptr)
{
}


ActiveShipSprite::~ActiveShipSprite()
{
}

void ActiveShipSprite::Init()
{
	SetBitmap( m_NormalBitmap );
	SetDestroy( false );
}


void ActiveShipSprite::Update()
{
	if( m_IsDestroyed )
	{
		SetBitmap( m_DestroyedBitmap );
	}
}


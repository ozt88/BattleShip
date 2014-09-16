#include "BFShipSprite.h"


BFShipSprite::BFShipSprite()
	:m_IsDestroyed(false) , m_NormalBitmap(nullptr) , m_DestroyedBitmap(nullptr)
{
}


BFShipSprite::~BFShipSprite()
{
}

void BFShipSprite::Init()
{
	SetBitmap( m_NormalBitmap );
	SetDestroy( false );
}


void BFShipSprite::Update()
{
	if( m_IsDestroyed )
	{
		SetBitmap( m_DestroyedBitmap );
	}
}


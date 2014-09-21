/************************************************************************/
/*
Class:		ActiveShipSprite

설명:		터지면 비트맵이 바뀌는 배 스프라이트

추가기능:
*/
/************************************************************************/
#pragma once
#include "D2DSprite.h"
class ActiveShipSprite :
	public D2DSprite
{
public:
	ActiveShipSprite();
	~ActiveShipSprite();

	void		Init();
	void		Update();
	void		SetNormalBitmap(Bitmap* bitmap) {m_NormalBitmap = bitmap; }
	void		SetDestroyedBitmap(Bitmap* bitmap) {m_DestroyedBitmap = bitmap; }
	void		SetDestroy(bool isDestroyed) {m_IsDestroyed = isDestroyed; }

private:

	bool		m_IsDestroyed;
	Bitmap*		m_NormalBitmap;
	Bitmap*		m_DestroyedBitmap;
};


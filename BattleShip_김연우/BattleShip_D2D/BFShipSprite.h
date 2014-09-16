#pragma once
#include "D2DSprite.h"
class BFShipSprite :
	public D2DSprite
{
public:
	BFShipSprite();
	~BFShipSprite();

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


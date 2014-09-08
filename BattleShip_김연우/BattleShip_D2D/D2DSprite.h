#pragma once
#include "Include.h"
#include "D2DObject.h"

class Bitmap;
class D2DRenderer;

class D2DSprite 
	:public D2DObject
{
public:
	D2DSprite();
	D2DSprite( std::wstring path );
	~D2DSprite();

	virtual void	Init();
	virtual void	Update();
	virtual void	Render();
	virtual void	Clear();

	void			SetBitmap( std::wstring path );
	void			SetBitmap(Bitmap* bitmap) {m_Bitmap = bitmap; }

protected:
	Bitmap*			m_Bitmap;
	D2DRenderer*	m_Renderer;
};


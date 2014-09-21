/************************************************************************/
/*
Class:		D2DSprite

설명:		실제 D2D의 기능을 수행하는 최하단 오브젝트
			비트맵 위주로 작동하며, 비트맵의 주소를 받아서 스프라이트의
			그림을 지정할 수 있다.

추가기능:	
*/
/************************************************************************/

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
	~D2DSprite();

	virtual void	Init();
	virtual void	Update();
	virtual void	Render();
	virtual void	Clear();

	Bitmap*			GetBitmap(){ return m_Bitmap;}
	void			SetBitmap(Bitmap* bitmap) {m_Bitmap = bitmap; }

protected:
	Bitmap*			m_Bitmap;
	D2DRenderer*	m_Renderer;
};


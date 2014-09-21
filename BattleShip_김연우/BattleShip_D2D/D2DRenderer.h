/************************************************************************/
/*
Class:		D2DRenderer

설명:		다이렉트 2D를 사용하는데 필요한 
			펙토리와 렌더타겟을 생성 관리

추가기능:	DrawText에 필요한 Write팩토리와 포멧 관리
*/
/************************************************************************/


#pragma once
#pragma comment(lib, "d2d1")
#pragma comment(lib, "Dwrite")

#include "Include.h"

class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	bool					Init();
	bool					Release();

	void					Clear();
	void					Begin();
	void					End();

	ID2D1Factory*			GetD2DFactory(){return m_D2DFactory;}
	ID2D1HwndRenderTarget*	GetHwndRenderTarget(){return m_D2DRenderTarget;}
	IDWriteTextFormat*		GetTextFormat() {return m_D2DTextFormat; }

private:
	ID2D1Factory*			m_D2DFactory;
	ID2D1HwndRenderTarget*	m_D2DRenderTarget;
	IDWriteFactory*			m_D2DWriteFactory;
	IDWriteTextFormat*		m_D2DTextFormat;

};


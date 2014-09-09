#include "UI.h"
#include "Bitmap.h"
#include "D2DSprite.h"

UI::UI()
{
	m_TitleBitmap = new Bitmap( L"Resource/Title.png" );
	m_TitleSprite = new D2DSprite();
	m_TitleSprite->SetBitmap( m_TitleBitmap );
	m_TitleSprite->SetObject( 0.f , 0.f , 6.f , 1.f );
	AddChild( m_TitleSprite );
}


UI::~UI()
{
}

void UI::Init()
{
	SetObject( POSX , POSY , WIDTH , HEIGTH );
	m_BoxWidth = m_Width / SHIP_NUM;
	m_BoxHeight = m_Height / SHIP_NUM;
	m_ScaleX = m_BoxWidth;
	m_ScaleY = m_BoxHeight;
}

void UI::Render()
{
	D2DObject::Render();
}

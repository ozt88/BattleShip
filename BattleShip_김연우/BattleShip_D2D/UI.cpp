#include "UI.h"
#include "D2DSprite.h"

UI::UI()
{
	m_Title = new D2DSprite();
}


UI::~UI()
{
}

void UI::Init()
{
	
	m_Width = WIDTH;
	m_Height = HEIGTH;
	m_PosX = POSX;
	m_PosY = POSY;
	m_BoxWidth = m_Width / SHIP_NUM;
	m_BoxHeight = m_Height / SHIP_NUM;
	m_ScaleX = m_BoxWidth;
	m_ScaleY = m_BoxHeight;
	m_Title->SetBitmap( L"Resource/Title.png" );
	m_Title->Width( 6 );
	m_Title->Height( 1 );
	AddChild( m_Title );

}

void UI::Render()
{
	D2DObject::Render();
}

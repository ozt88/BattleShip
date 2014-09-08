#include "D2DSprite.h"
#include "BattleShipApp.h"
#include "Bitmap.h"
#include "D2DRenderer.h"

D2DSprite::D2DSprite()
	:m_Bitmap(nullptr)
{
	m_Matrix = D2D1::Matrix3x2F::Identity();
	m_Renderer = BattleShipApp::GetInstance()->GetD2DRenderer();
}

D2DSprite::D2DSprite( std::wstring path )
{
	m_Matrix = D2D1::Matrix3x2F::Identity();
	m_Renderer = BattleShipApp::GetInstance()->GetD2DRenderer();
	m_Bitmap = new Bitmap( path );
	m_Width = 1;
	m_Height = 1;
}



D2DSprite::~D2DSprite()
{
	Clear();
}

void D2DSprite::Render()
{
	D2DObject::Render();
	m_Renderer->GetHwndRenderTarget()->SetTransform( m_Matrix );
	m_Renderer->GetHwndRenderTarget()->DrawBitmap( m_Bitmap->GetD2D1Bitmap() , D2D1::RectF( 0, 0 , m_Width , m_Height ));
}

void D2DSprite::Clear()
{
	m_Bitmap->Release();
	m_Renderer = nullptr;
}

void D2DSprite::Init()
{
	
}

void D2DSprite::Update()
{

}

void D2DSprite::SetBitmap( std::wstring path )
{
	if( m_Bitmap != nullptr )
	{
		m_Bitmap->Release();
	}
	m_Bitmap = new Bitmap( path );
	m_Width = m_Bitmap->GetD2D1Bitmap()->GetSize().width;
	m_Height = m_Bitmap->GetD2D1Bitmap()->GetSize().height;
}



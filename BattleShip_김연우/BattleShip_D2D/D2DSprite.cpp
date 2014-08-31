#include "D2DSprite.h"
#include "BattleShipApp.h"
#include "Bitmap.h"
#include "D2DRenderer.h"

D2DSprite::D2DSprite()
	:m_Renderer(nullptr) , m_Bitmap(nullptr) , m_PosX(0.f) , m_PosY(0.f)
{
	m_Matrix = D2D1::Matrix3x2F::Identity();
}

D2DSprite::D2DSprite( std::wstring path )
{
	m_Matrix = D2D1::Matrix3x2F::Identity();
	m_Renderer = BattleShipApp::GetInstance()->GetD2DRenderer();
	m_Bitmap = new Bitmap( path );
	_ASSERT( m_Bitmap->GetD2D1Bitmap() != nullptr );
	m_Width = m_Bitmap->GetD2D1Bitmap()->GetSize().width;
	m_Height = m_Bitmap->GetD2D1Bitmap()->GetSize().height;
}



D2DSprite::~D2DSprite()
{
	Clear();
}

void D2DSprite::Render()
{
	//m_Renderer->Begin();
	m_Matrix = D2D1::Matrix3x2F::Translation( m_PosX , m_PosY );
	m_Renderer->GetHwndRenderTarget()->SetTransform( m_Matrix );
	m_Renderer->GetHwndRenderTarget()->DrawBitmap( m_Bitmap->GetD2D1Bitmap() , D2D1::RectF( 0, 0 , m_Width , m_Height ));
 	//m_Renderer->End();
}

void D2DSprite::Clear()
{
	m_Bitmap->Release();
	m_Renderer = nullptr;
}

void D2DSprite::Init()
{
	
}



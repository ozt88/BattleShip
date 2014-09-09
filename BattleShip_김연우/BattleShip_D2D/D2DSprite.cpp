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
	m_Bitmap = nullptr;
	m_Renderer = nullptr;
}

void D2DSprite::Init()
{
}

void D2DSprite::Update()
{

}



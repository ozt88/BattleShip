#include "D2DScene.h"
#include "BattleShipApp.h"


D2DScene::D2DScene()
{
	RECT rt;
	GetWindowRect( BattleShipApp::GetInstance()->GetHWND() , &rt );
	m_Width = (float)(rt.right - rt.left);
	m_Height = ( float )(rt.bottom - rt.top);
}


D2DScene::~D2DScene()
{
}

void D2DScene::Init()
{
}

void D2DScene::Render()
{
	m_Renderer->Begin();
	m_Renderer->Clear();
	D2DObject::Render();
	m_Renderer->End();

}

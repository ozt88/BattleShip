#include "EndObject.h"
#include "GameManager.h"
#include "D2DSprite.h"
#include "Bitmap.h"
#include "Enum.h"
#include "BattleShipApp.h"

EndObject::EndObject()
{
	SetObject( POSX , POSY , WIDTH , HEIGTH );
	m_ScaleX = m_Width / BOX_NUM_X;
	m_ScaleY = m_Height / BOX_NUM_Y;

	m_EndTitle = new D2DSprite();
	m_RetryButton = new D2DSprite();
	m_ExitButton = new D2DSprite();

	m_EndTitleBitmap = new Bitmap( L"Resource/EndTitle1.png" );
	m_RetryUnmarkedBitmap = new Bitmap( L"Resource/Retry.png" );
	m_RetryMarkedBitmap = new Bitmap( L"Resource/Retry1.png" );
	m_ExitUnmarkedBitmap = new Bitmap( L"Resource/Exit.png" );
	m_ExitMarkedBitmap = new Bitmap( L"Resource/Exit1.png" );

	m_MousePointer = new CPoint();

	m_EndTitle->SetBitmap( m_EndTitleBitmap );
	m_RetryButton->SetBitmap( m_RetryUnmarkedBitmap );
	m_ExitButton->SetBitmap( m_ExitUnmarkedBitmap );
	

	m_EndTitle->SetObject( 0 , 0 , BOX_NUM_X , BOX_NUM_Y - 1 );
	m_RetryButton->SetObject( 0 , 2 , BOX_NUM_X / 2 , BOX_NUM_Y * 1 / 3 );
	m_ExitButton->SetObject( 1 , 2 , BOX_NUM_X / 2 , BOX_NUM_Y * 1 / 3 );

}


EndObject::~EndObject()
{
	m_EndTitle->Clear();
	m_RetryButton->Clear();
	m_ExitButton->Clear();
	m_EndTitleBitmap->Release();
	m_RetryMarkedBitmap->Release();
	m_RetryUnmarkedBitmap->Release();
	m_ExitMarkedBitmap->Release();
	m_ExitUnmarkedBitmap->Release();
}

void EndObject::Init( std::wstring winnerName , int endTurnNum )
{

	m_WinnerName = winnerName + L" in " + std::to_wstring( endTurnNum ) + L" turn";

	AddChild( m_EndTitle );
	AddChild( m_RetryButton );
	AddChild( m_ExitButton );
	GetRenderer()->GetHwndRenderTarget()->
		CreateSolidColorBrush
		( D2D1::ColorF( D2D1::ColorF::White ) , &m_Brush );
}

void EndObject::Render()
{
	D2DObject::Render(); 

	D2DRenderer* renderer = GetRenderer();

	renderer->GetHwndRenderTarget()->
		SetTransform( D2D1::Matrix3x2F::Identity() );

	renderer->GetHwndRenderTarget()
		->DrawTextA(
		 m_WinnerName.c_str(),
		 m_WinnerName.length(),
		renderer->GetTextFormat() ,
		D2D1::RectF(0 , 0 , 1000 , 300 ) ,
		m_Brush
		);
	//Super HardCoding....
}

void EndObject::Update()
{
	if( GameManager::GetInstance()->GetGameState() == GAME_END )
	{
		if( IsMouseOverRetry() && m_RetryButton->GetBitmap() != m_RetryMarkedBitmap )
		{
			m_RetryButton->SetBitmap( m_RetryMarkedBitmap );
		}
		else if( IsMouseOverRetry() && GetKeyState( VK_LBUTTON ) & 0x8000 )
		{
			GameManager::GetInstance()->SetGameState( RESET );
		}
		else if( !IsMouseOverRetry() && m_RetryButton->GetBitmap() != m_RetryUnmarkedBitmap )
		{
			m_RetryButton->SetBitmap( m_RetryUnmarkedBitmap );
		}

		if( IsMouseOverExit() && m_ExitButton->GetBitmap() != m_ExitMarkedBitmap )
		{
			m_ExitButton->SetBitmap( m_ExitMarkedBitmap );
		}
		else if( IsMouseOverExit() && GetKeyState( VK_LBUTTON ) & 0x8000 )
		{
			GameManager::GetInstance()->SetGameState( QUIT_GAME );
		}
		else if( !IsMouseOverExit() && m_ExitButton->GetBitmap() != m_ExitUnmarkedBitmap )
		{
			m_ExitButton->SetBitmap( m_ExitUnmarkedBitmap );
		}
	}

	D2DObject::Update();
}

bool EndObject::IsMouseOverRetry()
{
	
	GetCursorPos( m_MousePointer );
	ScreenToClient( BattleShipApp::GetInstance()->GetHWND() , m_MousePointer );

	float x = ( float )m_MousePointer->x;
	float y = ( float )m_MousePointer->y;

	float startX , startY , endX , endY;
	startX = m_PosX + m_ScaleX * m_RetryButton->PosX();
	startY = m_PosY + m_ScaleY * m_RetryButton->PosY();
	endX = startX + m_ScaleX * m_RetryButton->Width();
	endY = startY + m_ScaleY * m_RetryButton->Height();

	return( m_MousePointer->x > startX && m_MousePointer->x < endX
		&& m_MousePointer->y > startY && m_MousePointer->y < endY );

}

bool EndObject::IsMouseOverExit()
{
	GetCursorPos( m_MousePointer );
	ScreenToClient( BattleShipApp::GetInstance()->GetHWND() , m_MousePointer );

	float x = ( float )m_MousePointer->x;
	float y = ( float )m_MousePointer->y;

	float startX , startY , endX , endY;
	startX = m_PosX + m_ScaleX * m_ExitButton->PosX();
	startY = m_PosY + m_ScaleY * m_ExitButton->PosY();
	endX = startX + m_ScaleX * m_ExitButton->Width();
	endY = startY + m_ScaleY * m_ExitButton->Height();

	return( m_MousePointer->x > startX && m_MousePointer->x < endX
			&& m_MousePointer->y > startY && m_MousePointer->y < endY );
}

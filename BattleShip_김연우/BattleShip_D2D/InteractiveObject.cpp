#include "InteractiveObject.h"
#include "GameManager.h"
#include "GameScene.h"
#include "D2DSprite.h"
#include "Bitmap.h"
#include "Enum.h"
#include "BattleShipApp.h"

InteractiveObject::InteractiveObject()
{
	//생성할때 필요한 비트맵과 스프라이트를 생성하고 자식에 추가, 위치를 지정한다.
	//##비트맵을 이렇게 남발하는것은 좋아보이지 않음...수정의 여지
	SetObject( POSX , POSY , WIDTH , HEIGTH );
	m_ScaleX = m_Width / BOX_NUM_X;
	m_ScaleY = m_Height / BOX_NUM_Y;

	m_MainSprite = new D2DSprite();
	m_LeftButton = new D2DSprite();
	m_RightButton = new D2DSprite();

	m_BootingTitleBitmap = new Bitmap( L"Resource/StartTitle.png" );
	m_SoloUnmarkedBitmap = new Bitmap( L"Resource/Solo.png" );
	m_SoloMarkedBitmap = new Bitmap( L"Resource/Solo1.png" );
	m_MultiUnmarkedBitmap = new Bitmap( L"Resource/Multi.png" );
	m_MultiMarkedBitmap = new Bitmap( L"Resource/Multi1.png" );

	m_EndTitleBitmap = new Bitmap( L"Resource/EndTitle1.png" );
	m_RetryUnmarkedBitmap = new Bitmap( L"Resource/Retry.png" );
	m_RetryMarkedBitmap = new Bitmap( L"Resource/Retry1.png" );
	m_ExitUnmarkedBitmap = new Bitmap( L"Resource/Exit.png" );
	m_ExitMarkedBitmap = new Bitmap( L"Resource/Exit1.png" );

	m_MousePointer = new CPoint();

	m_MainSprite->SetObject( 0 , 0 , BOX_NUM_X , BOX_NUM_Y - 1 );
	m_LeftButton->SetObject( 0 , 2 , BOX_NUM_X / 2 , BOX_NUM_Y * 1 / 3 );
	m_RightButton->SetObject( 1 , 2 , BOX_NUM_X / 2 , BOX_NUM_Y * 1 / 3 );
	
	AddChild( m_MainSprite );
	AddChild( m_LeftButton );
	AddChild( m_RightButton );
	GetRenderer()->GetHwndRenderTarget()->
		CreateSolidColorBrush
		( D2D1::ColorF( D2D1::ColorF::AntiqueWhite ) , &m_Brush );
}


InteractiveObject::~InteractiveObject()
{
	m_MainSprite->Clear();
	m_LeftButton->Clear();
	m_RightButton->Clear();

	m_EndTitleBitmap->Release();
	m_RetryMarkedBitmap->Release();
	m_RetryUnmarkedBitmap->Release();
	m_ExitMarkedBitmap->Release();
	m_ExitUnmarkedBitmap->Release();
}

void InteractiveObject::Init()
{
	m_Message = L"HELLO WORLD";
}

void InteractiveObject::Render()
{
	D2DObject::Render(); 

	D2DRenderer* renderer = GetRenderer();

	renderer->GetHwndRenderTarget()->
		SetTransform( D2D1::Matrix3x2F::Identity() );

	renderer->GetHwndRenderTarget()
		->DrawTextA(
		 m_Message.c_str(),
		 m_Message.length(),
		renderer->GetTextFormat() ,
		D2D1::RectF(0 , 0 , 1000 , 380 ) ,
		m_Brush
		);
	//Super HardCoding....
	//DrawText하는 RECT값이 어떤 의미인지 아직 잘 모르겠다...
	//matrix와의 관계는?
	//##수정의 여지
}

void InteractiveObject::Update()
{
	GameState state = GameManager::GetInstance()->GetGameState();
	//상호작용 오브젝트가 활성화된 상태가 어떤 것이냐에 따라
	//입력에 응답하는 방식이 달라진다.
	switch( state )
	{
		case GAME_WAIT:
			GameStartAction();
			break;
		case GAME_OVER:
			GameOverAction();
			break;
		case GAME_END:
			GameEndAction();
			break;
		default:
			break;

	}
	

	D2DObject::Update();
}

//마우스 오버인지 확인하는 함수
bool InteractiveObject::IsMouseOverLeftButton()
{
	//현재 마우스 포인터의 위치를 받아서 현재 윈도우의 상대적인 좌표로 변환한다.
	GetCursorPos( m_MousePointer );
	ScreenToClient( BattleShipApp::GetInstance()->GetHWND() , m_MousePointer );

	float x = ( float )m_MousePointer->x;
	float y = ( float )m_MousePointer->y;

	//마우스 오버 영역의 좌상단 좌표를 start 우하단 좌표를 end로 잡고 계산한다.
	float startX , startY , endX , endY;
	//scale을 활용 오브젝트 상대좌표에서 윈도우 상대좌표로 계산한다.
	startX = m_PosX + m_ScaleX * m_LeftButton->PosX();
	startY = m_PosY + m_ScaleY * m_LeftButton->PosY();
	endX = startX + m_ScaleX * m_LeftButton->Width();
	endY = startY + m_ScaleY * m_LeftButton->Height();
	//##발생문제, 윈도우 크기조절하면 이 마우스오버연산이 제대로 작동안한다.

	return( m_MousePointer->x > startX && m_MousePointer->x < endX
		&& m_MousePointer->y > startY && m_MousePointer->y < endY );
}

bool InteractiveObject::IsMouseOverRightButton()
{
	GetCursorPos( m_MousePointer );
	ScreenToClient( BattleShipApp::GetInstance()->GetHWND() , m_MousePointer );

	float x = ( float )m_MousePointer->x;
	float y = ( float )m_MousePointer->y;

	float startX , startY , endX , endY;
	startX = m_PosX + m_ScaleX * m_RightButton->PosX();
	startY = m_PosY + m_ScaleY * m_RightButton->PosY();
	endX = startX + m_ScaleX * m_RightButton->Width();
	endY = startY + m_ScaleY * m_RightButton->Height();

	return( m_MousePointer->x > startX && m_MousePointer->x < endX
			&& m_MousePointer->y > startY && m_MousePointer->y < endY );
}

void InteractiveObject::EndObjectInit()
{
	m_LeftButton->SetBitmap( m_RetryUnmarkedBitmap );
	m_RightButton->SetBitmap( m_ExitUnmarkedBitmap );
}

void InteractiveObject::StartObjectInit()
{
	m_MainSprite->SetBitmap( m_BootingTitleBitmap );
	m_LeftButton->SetBitmap( m_SoloUnmarkedBitmap );
	m_RightButton->SetBitmap( m_MultiUnmarkedBitmap );
}

//Action은 버튼클릭에 관련된 상호작용이다.
void InteractiveObject::GameStartAction()
{
	//마우스오버가되면 비트맵을 변경하고
	if( IsMouseOverLeftButton() && m_LeftButton->GetBitmap() != m_SoloMarkedBitmap )
	{
		m_LeftButton->SetBitmap( m_SoloMarkedBitmap );
	}
	//그상태에서 버튼이 눌리면 게임과 시스템의 상태를 변경한다.
	else if( IsMouseOverLeftButton() && GetKeyState( VK_LBUTTON ) & 0x8000 )
	{
		GameManager::GetInstance()->SetGameMode( SOLO );
		GameManager::GetInstance()->SetSystemState( SOLO_INIT );
	}
	//마우스 오버가 풀려도 비트맵을 변경
	else if( !IsMouseOverLeftButton() && m_LeftButton->GetBitmap() != m_SoloUnmarkedBitmap )
	{
		m_LeftButton->SetBitmap( m_SoloUnmarkedBitmap );
	}

	//오른쪽 버튼도 똑같다.
	if( IsMouseOverRightButton() && m_RightButton->GetBitmap() != m_MultiMarkedBitmap )
	{
		m_RightButton->SetBitmap( m_MultiMarkedBitmap );
	}
	else if( IsMouseOverRightButton() && GetKeyState( VK_LBUTTON ) & 0x8000 )
	{
		SetMessage( L"네트워크 연결중..." );
		GameManager::GetInstance()->SetGameMode( NETWORK );
		GameManager::GetInstance()->SetSystemState( NETWORK_INIT );
	}
	else if( !IsMouseOverRightButton() && m_RightButton->GetBitmap() != m_MultiUnmarkedBitmap )
	{
		m_RightButton->SetBitmap( m_MultiUnmarkedBitmap );
	}
}

void InteractiveObject::GameEndAction()
{
	if( IsMouseOverLeftButton() && m_LeftButton->GetBitmap() != m_RetryMarkedBitmap )
	{
		m_LeftButton->SetBitmap( m_RetryMarkedBitmap );
	}
	else if( IsMouseOverLeftButton() && GetKeyState( VK_LBUTTON ) & 0x8000 )
	{
		if( GameManager::GetInstance()->GetGameMode() == SOLO )
		{
			GameManager::GetInstance()->SetGameState( GAME_RESET );
		}
		else
		{
			GameManager::GetInstance()->SetSystemState( NETWORK_RUNNING );
		}
	}
	else if( !IsMouseOverLeftButton() && m_LeftButton->GetBitmap() != m_RetryUnmarkedBitmap )
	{
		m_LeftButton->SetBitmap( m_RetryUnmarkedBitmap );
	}

	if( IsMouseOverRightButton() && m_RightButton->GetBitmap() != m_ExitMarkedBitmap )
	{
		m_RightButton->SetBitmap( m_ExitMarkedBitmap );
	}
	else if( IsMouseOverRightButton() && GetKeyState( VK_LBUTTON ) & 0x8000 )
	{
		GameManager::GetInstance()->SetSystemState(SYSTEM_QUIT);
	}
	else if( !IsMouseOverRightButton() && m_RightButton->GetBitmap() != m_ExitUnmarkedBitmap )
	{
		m_RightButton->SetBitmap( m_ExitUnmarkedBitmap );
	}
}

void InteractiveObject::GameOverAction()
{
	if( IsMouseOverLeftButton() && m_LeftButton->GetBitmap() != m_RetryMarkedBitmap )
	{
		m_LeftButton->SetBitmap( m_RetryMarkedBitmap );
	}
	else if( IsMouseOverLeftButton() && GetKeyState( VK_LBUTTON ) & 0x8000 )
	{
		GameManager::GetInstance()->SetSystemState( START_INIT );
	}
	else if( !IsMouseOverLeftButton() && m_LeftButton->GetBitmap() != m_RetryUnmarkedBitmap )
	{
		m_LeftButton->SetBitmap( m_RetryUnmarkedBitmap );
	}

	if( IsMouseOverRightButton() && m_RightButton->GetBitmap() != m_ExitMarkedBitmap )
	{
		m_RightButton->SetBitmap( m_ExitMarkedBitmap );
	}
	else if( IsMouseOverRightButton() && GetKeyState( VK_LBUTTON ) & 0x8000 )
	{
		GameManager::GetInstance()->SetSystemState( SYSTEM_QUIT );
	}
	else if( !IsMouseOverRightButton() && m_RightButton->GetBitmap() != m_ExitUnmarkedBitmap )
	{
		m_RightButton->SetBitmap( m_ExitUnmarkedBitmap );
	}
}

#include "BattleShipApp.h"
#include "D2DRenderer.h"
#include "GameManager.h"

BattleShipApp* BattleShipApp::m_Instance = nullptr;

BattleShipApp::BattleShipApp()
	: m_hInstance( nullptr ) , m_hWnd( nullptr ) , m_Running( false )
{
	m_D2DRenderer = new D2DRenderer();
}

BattleShipApp::~BattleShipApp()
{
	if( m_D2DRenderer == nullptr )
	{
		delete m_D2DRenderer;
		m_D2DRenderer = nullptr;
	}
}


BattleShipApp* BattleShipApp::GetInstance()
{
	if( m_Instance == nullptr )
	{
		m_Instance = new BattleShipApp();
	}
	return m_Instance;
}

void BattleShipApp::ReleaseInstance()
{
	if( m_Instance != nullptr )
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

LRESULT CALLBACK BattleShipApp::WndProc( HWND hWnd , UINT iMessage , WPARAM wParam , LPARAM lParam )
{

	HDC hdc;
	PAINTSTRUCT ps;

	switch( iMessage )
	{
		case WM_CREATE:
			return 0;
// 		case WM_PAINT:
// 			hdc = BeginPaint( hWnd , &ps );
// 			EndPaint( hWnd , &ps );
// 			return 0;
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
	}
	return( DefWindowProc( hWnd , iMessage , wParam , lParam ) );
}

void BattleShipApp::Run()
{
	MSG message;

	while( true )
	{
		if( PeekMessage( &message , NULL , 0 , 0 , PM_REMOVE ) )
		{
			if( message.message == WM_QUIT )
			{
				return;
			}

			TranslateMessage( &message );
			DispatchMessage( &message );
		}
		m_GM->Render();
	}
}

bool BattleShipApp::Init( TCHAR* title , int width , int height )
{
	m_hInstance = GetModuleHandle( 0 );
	m_Running = true;

	CreateWindow_( title , width , height );

	ShowWindow( m_hWnd , SW_SHOWNORMAL );
	m_D2DRenderer->Init();
	m_GM = new GameManager();

	return true;
}

bool BattleShipApp::CreateWindow_( TCHAR* title , int width , int height )
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	WndClass.hCursor = LoadCursor( NULL , IDC_ARROW );
	WndClass.hIcon = LoadIcon( NULL , IDI_APPLICATION );
	WndClass.hInstance = m_hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = _T( "APPLICATION" );
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass( &WndClass );

	m_hWnd = CreateWindow( _T( "APPLICATION" ) , title , WS_OVERLAPPEDWINDOW ,
						   CW_USEDEFAULT , CW_USEDEFAULT ,
						   width , height , NULL , ( HMENU )NULL , m_hInstance , NULL );

	return true;
}

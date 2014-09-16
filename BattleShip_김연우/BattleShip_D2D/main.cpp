#include "BattleShipApp.h"

// void DevConsoleCreate()
// {
// 
// 	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
// 
// 	AllocConsole();
// 	std::wstring strW = L"Dev Console";
// 	SetConsoleTitle( strW.c_str() );
// 
// 	EnableMenuItem( GetSystemMenu( GetConsoleWindow() , FALSE ) , SC_CLOSE , MF_GRAYED );
// 	DrawMenuBar( GetConsoleWindow() );
// 
// 	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ) , &consoleInfo );
// 
// 	freopen( "conin$" , "r" , stdin );
// 	freopen( "conout$" , "w" , stdout );
// 	freopen( "conout$" , "w" , stderr );
// 
// 
// }


int APIENTRY WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance
					  , LPSTR lpszCmdParam , int nCmdShow )
{
	srand( ( unsigned )time( NULL ) );
	BattleShipApp::GetInstance()->Init( _T( "abc" ) , 1000 , 500 );
	BattleShipApp::GetInstance()->Run();
	BattleShipApp::ReleaseInstance();

	return 0;
}
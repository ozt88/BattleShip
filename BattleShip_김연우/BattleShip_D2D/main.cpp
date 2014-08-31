#include "BattleShipApp.h"

int APIENTRY WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance
					  , LPSTR lpszCmdParam , int nCmdShow )
{
	BattleShipApp::GetInstance()->Init( _T( "abc" ) , 1000 , 500 );
	BattleShipApp::GetInstance()->Run();
	BattleShipApp::ReleaseInstance();

	return 0;
}
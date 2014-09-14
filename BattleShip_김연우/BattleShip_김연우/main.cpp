// BattleShip_PP.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "GameManager.h"
#include "Ship.h"
#define COUNT 100

int _tmain(int argc, _TCHAR* argv[])
{
	srand( ( unsigned )time( NULL ) );
 	GameManager GM;
	for( int i = 0; i < COUNT; ++i )
	{
		GM.GameStart();
	}

	getchar();
	return 0;
}


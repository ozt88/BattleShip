// BattleShip_PP.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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


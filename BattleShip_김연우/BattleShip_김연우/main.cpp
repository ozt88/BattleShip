// BattleShip_PP.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "GameManager.h"
#include "Ship.h"
int _tmain(int argc, _TCHAR* argv[])
{
	srand( ( unsigned )time( NULL ) );
// 	GameManager GM;
// 	GM.GameStart();

	Ship ship;
	ship.SetHP( 100 );
	getchar();
	return 0;
}


// BattleShip_PP.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Player.h"
#include "Board.h"
#include "AirCraft.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "GameManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	GameManager gm;
	gm.GameStart();
	getchar();
	return 0;
}


#pragma once
#include "Ship.h"
class BattleShip : public Ship
{
public:
	BattleShip();
	BattleShip( float rowNum );
	~BattleShip();
	HitResult HitCheck( Position hitPos );
};


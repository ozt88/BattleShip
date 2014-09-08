#pragma once
#include "Ship.h"
class Destroyer : public Ship
{
public:
	Destroyer();
	Destroyer( float rowNum );
	~Destroyer();
	HitResult HitCheck( Position hitPos );

};


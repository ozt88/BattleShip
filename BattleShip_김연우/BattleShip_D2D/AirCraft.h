#pragma once
#include "Ship.h"
class AirCraft : public Ship
{
public:
	AirCraft();
	AirCraft( float rowNum );
	~AirCraft();
	HitResult HitCheck( Position hitPos );
};


#pragma once
#include "Ship.h"
class Cruiser : public Ship
{
public:
	Cruiser();
	Cruiser( float rowNum );
	~Cruiser();
	HitResult HitCheck( Position hitPos );

};


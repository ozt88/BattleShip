#include "stdafx.h"
#include "Cruiser.h"


Cruiser::Cruiser()
{
	m_MaxHP = 3;
	m_HP = m_MaxHP;
	m_Type = CRUISER;
	m_Name = "Cruiser";
}


Cruiser::~Cruiser()
{
}

HitResult Cruiser::HitCheck( Position hitPos )
{
	HitResult result = Ship::HitCheck( hitPos );
	return ( result == DESTROY ) ? DESTROY_CRUISER : result;
}
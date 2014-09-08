#pragma once
#include "D2DObject.h"
#include "Enum.h"

class BattleField :
	public D2DObject
{
public:
	BattleField();
	~BattleField();

	void					Init();
	void					Render();

private:
	ID2D1SolidColorBrush*	m_Brush;
	float					m_BoxWidth;
	float					m_BoxHeight;
	enum BFSize
	{

		POSX = 150,
		POSY = 0,
		WIDTH = 325,
		HEIGTH = 325,
	};

};


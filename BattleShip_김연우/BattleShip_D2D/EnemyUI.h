#pragma once
#include "D2DObject.h"

class D2DSprite;
class EnemyUI :
	public D2DObject
{
public:
	EnemyUI();
	~EnemyUI();
	
	void					Init();
	void					MakeDestroySprite(int size);

private:
	float					m_BoxWidth;
	float					m_BoxHeight;
	std::list<D2DSprite*>	m_ShipSprites;

	enum UISize
	{
		POSX = 850 ,
		POSY = 0 ,
		WIDTH = 150 ,
		HEIGTH = 325 ,
	};
};


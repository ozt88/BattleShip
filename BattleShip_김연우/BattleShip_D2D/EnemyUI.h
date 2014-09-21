/************************************************************************/
/*
Class:		UI

설명:		남은 적 기체 상황을 표시하는 오브젝트
			현재 게임에 투입된 적 기체와 그 상황을 표현할 수 있다.

			*UI클래스와 다를바 없어 보이나 타이틀 바와 
			HP Sprite Update가 불필요하다 생각하여 새로 만듬

추가기능:
*/
/************************************************************************/

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


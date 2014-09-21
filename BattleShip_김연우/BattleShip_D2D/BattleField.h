/************************************************************************/
/*
Class:		BattleField

설명:		전장의 상황을 표시하는 오브젝트
			정방형 맵을 DrawLine으로 그리고 그 위에 
			현재 게임에 참여한 배들을 위치에 맞게 출력

추가기능:
*/
/************************************************************************/
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
		BOX_NUM_X = MAP_WIDTH ,
		BOX_NUM_Y = MAP_HEIGHT ,
	};

};


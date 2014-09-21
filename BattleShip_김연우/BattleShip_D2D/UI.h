/************************************************************************/
/*
Class:		UI

설명:		유저의 현재 게임 상황을 표시하는 오브젝트
			현재 게임에 투입된 배들과 그 배의 HP Sprite를 생성, 관리

추가기능:	
*/
/************************************************************************/

#pragma once
#include "D2DObject.h"
#include "Enum.h"

class Bitmap;
class D2DSprite;
class UI :
	public D2DObject
{
public:
	UI();
	~UI();

	void					Init();
	void					Render();

private:
	//타이틀 바 (예쁘게 보여주기 위함...)
	D2DSprite*				m_TitleSprite;
	Bitmap*					m_TitleBitmap;
	//주어진 스크린을 박스 단위로 나누어서 사용하기 위한 값
	//일반적으로 전체 너비(높이)/박스 갯수로 구한다.
	float					m_BoxWidth;
	float					m_BoxHeight;
	enum UISize
	{
		POSX = 0 ,
		POSY = 0 ,
		WIDTH = 150 ,
		HEIGTH = 325 ,
	};
};


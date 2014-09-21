/************************************************************************/
/*
Class:		InteractiveObject

설명:		유저의 인풋을 받기위한 오브젝트

			글씨 출력으로 현재 정보가 나타나는 MainSprite
			양자 택일의 선택을 할 수 있는 Left/ RightButton 
			위 스프라이트들을 묶어서 생성, 관리, 출력

			이 오브젝트가 GameScene에 AddChild되면 
			업데이트 할때 유저의 마우스 입력을 받아서 
			게임, 시스템 상태를 변경할 수 있다.

추가기능:	마우스 오버가 되면 유저에게 작동한다는 느낌을 주기위해서
			버튼 스프라이트의 비트맵을 전환한다.

			MainSprite에 DrawText를 이용하여 
			변화된 상태나 게임의 정보를 출력할 수 있다.
*/
/************************************************************************/
#pragma once
#include "D2DObject.h"

class D2DSprite;
class Bitmap;
class InteractiveObject :
	public D2DObject
{
public:
	InteractiveObject();
	~InteractiveObject();

	void					Init();
	void					Render();
	void					Update();

	void					SetMessage(std::wstring msg) { m_Message = msg; }
	void					EndObjectInit();
	void					StartObjectInit();

	bool					IsMouseOverRetry();
	bool					IsMouseOverExit();
	void					GameEndAction();
	void					GameStartAction();
	void					GameOverAction();

private:
	D2DSprite*				m_MainSprite;
	D2DSprite*				m_LeftButton;
	D2DSprite*				m_RightButton;

	Bitmap*					m_BootingTitleBitmap;
	Bitmap*					m_SoloUnmarkedBitmap;
	Bitmap*					m_SoloMarkedBitmap;
	Bitmap*					m_MultiUnmarkedBitmap;
	Bitmap*					m_MultiMarkedBitmap;

	Bitmap*					m_EndTitleBitmap;
	Bitmap*					m_RetryUnmarkedBitmap;
	Bitmap*					m_RetryMarkedBitmap;
	Bitmap*					m_ExitUnmarkedBitmap;
	Bitmap*					m_ExitMarkedBitmap;

	ID2D1SolidColorBrush*	m_Brush;
	std::wstring			m_Message;

	CPoint*					m_MousePointer;

	enum ETSize
	{
		POSX = 350 ,
		POSY = 100 ,
		WIDTH = 300 ,
		HEIGTH = 200 ,
		BOX_NUM_X = 2,
		BOX_NUM_Y = 3,
	};

};


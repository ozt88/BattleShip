/************************************************************************/
/*
Class:		InteractiveObject

����:		������ ��ǲ�� �ޱ����� ������Ʈ

			�۾� ������� ���� ������ ��Ÿ���� MainSprite
			���� ������ ������ �� �� �ִ� Left/ RightButton 
			�� ��������Ʈ���� ��� ����, ����, ���

			�� ������Ʈ�� GameScene�� AddChild�Ǹ� 
			������Ʈ �Ҷ� ������ ���콺 �Է��� �޾Ƽ� 
			����, �ý��� ���¸� ������ �� �ִ�.

�߰����:	���콺 ������ �Ǹ� �������� �۵��Ѵٴ� ������ �ֱ����ؼ�
			��ư ��������Ʈ�� ��Ʈ���� ��ȯ�Ѵ�.

			MainSprite�� DrawText�� �̿��Ͽ� 
			��ȭ�� ���³� ������ ������ ����� �� �ִ�.
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

	bool					IsMouseOverLeftButton();
	bool					IsMouseOverRightButton();
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


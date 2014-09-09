#pragma once
#include "D2DObject.h"

class D2DSprite;
class Bitmap;
class EndObject :
	public D2DObject
{
public:
	EndObject();
	~EndObject();

	void					Init(std::wstring winnerName, int endTurnNum);
	void					Render();
	void					Update();
	bool					IsMouseOverRetry();
	bool					IsMouseOverExit();


private:
	D2DSprite*				m_EndTitle;
	D2DSprite*				m_RetryButton;
	D2DSprite*				m_ExitButton;

	Bitmap*					m_EndTitleBitmap;
	Bitmap*					m_RetryUnmarkedBitmap;
	Bitmap*					m_RetryMarkedBitmap;

	Bitmap*					m_ExitUnmarkedBitmap;
	Bitmap*					m_ExitMarkedBitmap;

	ID2D1SolidColorBrush*	m_Brush;
	std::wstring			m_WinnerName;

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


#pragma once
#include "D2DObject.h"
#include "Enum.h"

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
	D2DSprite*				m_Title;
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


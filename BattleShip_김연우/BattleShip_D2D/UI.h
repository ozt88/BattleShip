/************************************************************************/
/*
Class:		UI

����:		������ ���� ���� ��Ȳ�� ǥ���ϴ� ������Ʈ
			���� ���ӿ� ���Ե� ���� �� ���� HP Sprite�� ����, ����

�߰����:	
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
	//Ÿ��Ʋ �� (���ڰ� �����ֱ� ����...)
	D2DSprite*				m_TitleSprite;
	Bitmap*					m_TitleBitmap;
	//�־��� ��ũ���� �ڽ� ������ ����� ����ϱ� ���� ��
	//�Ϲ������� ��ü �ʺ�(����)/�ڽ� ������ ���Ѵ�.
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


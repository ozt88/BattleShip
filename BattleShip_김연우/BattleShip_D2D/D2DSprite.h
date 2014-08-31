#pragma once
#include "Include.h"

class Bitmap;
class D2DRenderer;

class D2DSprite 
{
public:
	D2DSprite();
	D2DSprite( std::wstring path );
	~D2DSprite();

	void Init();
	void Update();
	void Render();
	void Clear();

	float PosX() const {return m_PosX;}
	void PosX( float val ) {m_PosX = val;}
	float PosY() const {return m_PosY;}
	void PosY( float val ){m_PosY = val;}

private:
	float m_Width;
	float m_Height;
	float m_PosX;
	float m_PosY;

	D2D1::Matrix3x2F m_Matrix;
	Bitmap* m_Bitmap;
	D2DRenderer* m_Renderer;
};


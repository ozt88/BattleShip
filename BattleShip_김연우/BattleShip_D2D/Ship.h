#pragma once
class D2DSprite;
class Ship
{
public:
	Ship();
	~Ship();

	void Render();
	float GetPosX() const
	{
		return m_PosX;
	}
	void SetPosX( float val );

	float GetPosY() const
	{
		return m_PosY;
	}
	void SetPosY( float val );


private:
	D2DSprite*	m_Sprite;
	float		m_PosX;
	float		m_PosY;
};


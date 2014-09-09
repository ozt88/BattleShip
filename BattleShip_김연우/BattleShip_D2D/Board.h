#pragma once
#include "Include.h"
#include "Enum.h"

class D2DSprite;
class Bitmap;
class Board
{
public:
	Board();
	~Board();

	int						GetMaxWidth(){return m_Width;}
	int						GetMaxHeight(){return m_Height;}
	std::vector<D2DSprite*>	GetTileList() {return m_TileList; }
	void					MapUpdate( Position position , HitResult hitResult );
	void					InitBoard();
	bool					IsWater( Position checkPos );
	bool					IsOutOfBoard( Position checkPos );

private:

	int						m_Width;
	int						m_Height;
	HitResult**				m_Board;
	std::vector<D2DSprite*>	m_TileList;
	Bitmap*					m_NormalTile;
	Bitmap*					m_MissedTile;
	Bitmap*					m_HitTile;
};


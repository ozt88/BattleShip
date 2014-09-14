#pragma once
#include "Include.h"
#include "Enum.h"

class D2DSprite;
class Bitmap;
struct Box
{
	HitResult	result;
	int			probability;
};

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
	
	void					ScaleBoardProb(Position checkPos , int scale) { m_Board[checkPos.m_X][checkPos.m_Y].probability *= scale; }
	int						GetBoardProb(Position checkPos) { return m_Board[checkPos.m_X][checkPos.m_Y].probability; }
	HitResult				GetBoardStatus(int x , int y) {return m_Board[x][y].result; }
	HitResult				GetBoardStatus(Position checkPos) { return m_Board[checkPos.m_X][checkPos.m_Y].result; }
	
	void					IncreaseProbablity( int x , int y , int shipSize , bool isVertical);
	void					IncreaseProbablity( int x , int y , int shipSize , Direction dir );
	void					ClearProb();

private:

	int						m_Width;
	int						m_Height;
	Box**					m_Board;
	std::vector<D2DSprite*>	m_TileList;
	Bitmap*					m_NormalTile;
	Bitmap*					m_MissedTile;
	Bitmap*					m_HitTile;
};


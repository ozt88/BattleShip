#pragma once
#include "Enums.h"

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

	int			GetMaxWidth() {return m_Width;}
	int			GetMaxHeight() {return m_Height;}
	void		MapUpdate( Position position , HitResult hitResult );
	void		InitBoard();
	bool		IsWater( Position checkPos );
	void		PrintBoard();
	bool		IsOutOfBoard( Position checkPos );

	int			GetBoardProb(Position checkPos) { return m_Board[checkPos.m_X][checkPos.m_Y].probability; }
	HitResult	GetBoardStatus(int x , int y) {return m_Board[x][y].result; }
	void		IncreaseProbablity( int x , int y , int shipSize , bool isVertical);
	void		ClearProb();

private:

	int			m_Width;
	int			m_Height;
	Box**		m_Board;

};


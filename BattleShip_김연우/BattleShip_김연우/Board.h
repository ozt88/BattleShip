#pragma once
#include "Enums.h"


class Board
{
public:
	Board();
	~Board();

	int		 GetMaxWidth() {return m_Width;}
	int		 GetMaxHeight() {return m_Height;}
	void	 MapUpdate( Position position , HitResult hitResult );
	void	 InitBoard();
	bool	 IsWater( Position checkPos );
	void	 PrintBoard();
	bool	 IsOutOfBoard( Position checkPos );

private:

	int			m_Width;
	int			m_Height;
	HitResult** m_Board;

};


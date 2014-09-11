#include "stdafx.h"
#include "Board.h"

Board::Board()
{
	m_Width = 8;
	m_Height = 8;
	m_Board = new Box*[m_Height];
	for( int i = 0; i < m_Height; i++ )
	{
		m_Board[i] = new Box[m_Width];
		for( int j = 0; j < m_Width; ++j )
		{
			m_Board[i][j].result = WATER;
			m_Board[i][j].probability = 0;
		}
	}
}


Board::~Board()
{
	for( int i = 0; i < m_Height; ++i )
	{
		delete m_Board[i];
	}
	delete m_Board;
}

bool Board::IsOutOfBoard( Position checkPos )
{
	return ( checkPos.m_X < 0 || checkPos.m_X >= m_Width
			 || checkPos.m_Y < 0 || checkPos.m_Y >= m_Height );
}

bool Board::IsWater( Position checkPos )
{
	return m_Board[checkPos.m_X][checkPos.m_Y].result == WATER;
}

void Board::PrintBoard()
{
	for( int i = 0; i < m_Height; ++i )
	{
		for( int j = 0; j < m_Width; ++j )
		{
			if( m_Board[i][j].result == WATER )
			{
				printf_s( " ~ %d " , m_Board[i][j].probability);
			}
			else if( m_Board[i][j].result == MISS)
			{
				printf_s( " X %d " , m_Board[i][j].probability );
			}
			else
			{
				printf_s( " O %d " , m_Board[i][j].probability );
			}
		}
		printf_s( "\n\n" );
	}
}

void Board::InitBoard()
{
	for( int x = 0; x < m_Height; x++ )
	{
		for( int y = 0; y < m_Width; ++y )
		{
			m_Board[x][y].result = WATER;
			m_Board[x][y].probability = 0;
		}
	}
}

void Board::MapUpdate( Position position , HitResult hitResult )
{
	m_Board[position.m_X][position.m_Y].result = hitResult; 
}

void Board::IncreaseProbablity( int x , int y , int shipSize , bool isVertical )
{
	int head = isVertical ? y : x;
	int tail = head + shipSize - 1;
	for( int i = head; i <= tail; ++i )
	{
		if( isVertical )
		{
			m_Board[x][i].probability++;
		}
		else
		{
			m_Board[i][y].probability++;
		}
	}
	
}

void Board::ClearProb()
{
	for( int x = 0; x < m_Height; x++ )
	{
		for( int y = 0; y < m_Width; ++y )
		{
			m_Board[x][y].probability = 0;
		}
	}
}





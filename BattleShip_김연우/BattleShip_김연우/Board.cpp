#include "stdafx.h"
#include "Board.h"

Board::Board()
{
	m_Width = 8;
	m_Height = 8;
	m_Board = new HitResult*[m_Height];
	for( int i = 0; i < m_Height; i++ )
	{
		m_Board[i] = new HitResult[m_Width];
		for( int j = 0; j < m_Width; ++j )
		{
			m_Board[i][j] = RESULT_NONE;
		}
	}
}


Board::~Board()
{
}

bool Board::IsOutOfBoard( Position checkPos )
{
	return ( checkPos.m_X < 0 || checkPos.m_X >= m_Width
			 || checkPos.m_Y < 0 || checkPos.m_Y >= m_Height );
}

bool Board::IsWater( Position checkPos )
{
	return m_Board[checkPos.m_X][checkPos.m_Y] == RESULT_NONE;
}

void Board::PrintBoard()
{
	for( int i = 0; i < m_Height; ++i )
	{
		for( int j = 0; j < m_Width; ++j )
		{
			if( m_Board[i][j] == RESULT_NONE )
			{
				printf_s( " ~ " );
			}
			else
			{
				printf_s( " X " );
			}
		}
		printf_s( "\n" );
	}
}

void Board::InitBoard()
{
	for( int i = 0; i < m_Height; i++ )
	{
		for( int j = 0; j < m_Width; ++j )
		{
			m_Board[i][j] = RESULT_NONE;
		}
	}
}

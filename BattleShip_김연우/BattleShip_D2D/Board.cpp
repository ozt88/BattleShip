#include "Board.h"
#include "Bitmap.h"
#include "D2DSprite.h"

Board::Board()
{
	m_Width = MAP_WIDTH;
	m_Height = MAP_HEIGHT;
	m_Board = new HitResult*[m_Height];
	for( int i = 0; i < m_Height; i++ )
	{
		m_Board[i] = new HitResult[m_Width];
		for( int j = 0; j < m_Width; ++j )
		{
			m_Board[i][j] = WATER;
			m_TileList.push_back( new D2DSprite() );
		}
	}
	m_NormalTile = new Bitmap(L"Resource/NormalTile.png");
	m_MissedTile = new Bitmap( L"Resource/MissedTile.png" );
	m_HitTile = new Bitmap( L"Resource/HitTile.png" );
}


Board::~Board()
{
	for( int i = 0; i < m_Height; ++i )
	{
		delete m_Board[i];
	}
	delete m_Board;
	m_MissedTile->Release();
	m_NormalTile->Release();
	m_HitTile->Release();
}

bool Board::IsOutOfBoard( Position checkPos )
{
	return ( checkPos.m_X < 0 || checkPos.m_X >= m_Width
			 || checkPos.m_Y < 0 || checkPos.m_Y >= m_Height );
}

bool Board::IsWater( Position checkPos )
{
	return m_Board[checkPos.m_X][checkPos.m_Y] == WATER;
}

void Board::InitBoard()
{
	for( int i = 0; i < m_Height; i++ )
	{
		for( int j = 0; j < m_Width; ++j )
		{
			m_Board[i][j] = WATER;
			m_TileList[i*m_Width + j]->SetBitmap( m_NormalTile );
			m_TileList[i*m_Width + j]->SetObject( ( float )i , ( float )j , 
												  ( float )1 , ( float )1 );
		}
	}
}

void Board::MapUpdate( Position position , HitResult hitResult )
{
	_ASSERT( hitResult != WATER );
	m_Board[position.m_X][position.m_Y] = hitResult;
	if( hitResult == MISS )
	{
		m_TileList[position.m_X* m_Width + position.m_Y]->SetBitmap( m_MissedTile );
	}
	else
	{
		m_TileList[position.m_X* m_Width + position.m_Y]->SetBitmap( m_HitTile );
	}
}

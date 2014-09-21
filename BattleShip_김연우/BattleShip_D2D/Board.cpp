#include "Board.h"
#include "Bitmap.h"
#include "D2DSprite.h"

Board::Board()
{
	m_Width = MAP_WIDTH;
	m_Height = MAP_HEIGHT;
	m_Board = new Box*[m_Height];
	for( int i = 0; i < m_Height; i++ )
	{
		m_Board[i] = new Box[m_Width];
		for( int j = 0; j < m_Width; ++j )
		{
			m_Board[i][j].result = WATER;
			//보드 갯수만큼 타일스프라이트 생성
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
		SafeDelete(m_Board[i]);
	}
	SafeDelete(m_Board);
	m_MissedTile->Release();
	m_NormalTile->Release();
	m_HitTile->Release();
}

bool Board::IsOutOfBoard( const Position& checkPos )
{
	return ( checkPos.m_X < 0 || checkPos.m_X >= m_Width
			 || checkPos.m_Y < 0 || checkPos.m_Y >= m_Height );
}

bool Board::IsWater( Position checkPos )
{
	if( !checkPos.isValid() )
	{
		return false;
	}
	return m_Board[checkPos.m_X][checkPos.m_Y].result == WATER;
}

void Board::InitBoard()
{
	for( int x = 0; x < m_Height; x++ )
	{
		for( int y = 0; y < m_Width; ++y )
		{
			m_Board[x][y].result = WATER;
			m_Board[x][y].probability = 0;
			//보드 초기화할때 모든 비트맵들을 노멀타일로 만들어준다.
			m_TileList[x*m_Width + y]->SetBitmap( m_NormalTile );
			m_TileList[x*m_Width + y]->SetObject( ( float )x , ( float )y , 
												  ( float )1 , ( float )1 );
		}
	}
}

//위치와 결과값을 인자로 받아서 그 위치의 BOX값과 스프라이트 비트맵을 변경
void Board::MapUpdate( const Position& position , HitResult hitResult )
{
	_ASSERT( hitResult != WATER );
	m_Board[position.m_X][position.m_Y].result = hitResult;
	if( hitResult == MISS )
	{
		m_TileList[position.m_X* m_Width + position.m_Y]->SetBitmap( m_MissedTile );
	}
	else
	{
		m_TileList[position.m_X* m_Width + position.m_Y]->SetBitmap( m_HitTile );
	}
}

//배 크기만큼의 Box들에 확률값을 상승시킨다.
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

//전 맵 확률 초기화
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
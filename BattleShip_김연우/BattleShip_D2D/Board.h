/************************************************************************/
/*
Class:		Board

설명:		게임에서 가능한 각 위치에 대한 정보를 관리하는 클래스
			각 위치(Position)당 Box정보(현재 위치상태와 확률정보)를 갖는다.
			플레이어의 명령에 따라서 현재 위치상태와 확률정보를 
			갱신, 전송할 수 있다.

			각 위치별 타일 스프라이트를 가지고 있어, 위치 상태가 변화하면
			타일 스프라이트의 비트맵을 전환하여 출력한다.

추가기능:
*/
/************************************************************************/

#pragma once
#include "Include.h"
#include "Enum.h"

class D2DSprite;
class Bitmap;
//맵들의 한칸한칸이 가지고 있는 정보
//현재 맵의 상태를 HitResult로 표현, 맵의 확률을 int로 표현
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
	void					MapUpdate( const Position& position , HitResult hitResult );
	void					InitBoard();
	bool					IsWater( Position checkPos );
	bool					IsOutOfBoard( const Position& checkPos );
	
	void					SetBoardStatus(const Position& checkPos, HitResult hitResult) { m_Board[checkPos.m_X][checkPos.m_Y].result = hitResult; }
	void					ScaleBoardProb(const Position& checkPos , int scale) { m_Board[checkPos.m_X][checkPos.m_Y].probability *= scale; }
	int						GetBoardProb(const Position& checkPos) { return m_Board[checkPos.m_X][checkPos.m_Y].probability; }
	HitResult				GetBoardStatus(int x , int y) {return m_Board[x][y].result; }
	HitResult				GetBoardStatus(const Position& checkPos) { return m_Board[checkPos.m_X][checkPos.m_Y].result; }
	
	void					IncreaseProbablity( int x , int y , int shipSize , bool isVertical);
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


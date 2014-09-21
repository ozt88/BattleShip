/************************************************************************/
/* 
Class:		BattleShipApp

설명:		배틀쉽 게임 전체를 포괄하는 App 싱글톤 클래스
			메인함수에서 돌아가는 
			윈도우 Class, Proc, 게임루프를 생성 관리

추가기능:	게임 내부에서 싱글톤을 활용하여
			윈도우 핸들, 인스턴스, 렌더러에 접근할 수 있게 함.
*/
/************************************************************************/


#pragma once
#include "Include.h"

class D2DRenderer;
class GameManager;

class BattleShipApp
{
public:
	static BattleShipApp*	GetInstance();
	static void				ReleaseInstance();

	void					Run();
	bool					Init( TCHAR* title , int width , int height );

	HWND					GetHWND(){return m_hWnd;}
	HINSTANCE				GetHInstance(){return m_hInstance;}
	D2DRenderer*			GetD2DRenderer(){return m_D2DRenderer;}

private:
	static LRESULT CALLBACK WndProc( HWND hWnd , UINT iMessage , WPARAM wParam , LPARAM lParam );
	bool					CreateWindow_( TCHAR* title , int width , int height );

	BattleShipApp();
	~BattleShipApp();

private:
	static BattleShipApp*	m_Instance;
	bool					m_Running;
	GameManager*			m_GM;
	HWND					m_hWnd;
	HINSTANCE				m_hInstance;
	D2DRenderer*			m_D2DRenderer;
};



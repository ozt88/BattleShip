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



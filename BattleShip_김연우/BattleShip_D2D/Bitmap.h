/************************************************************************/
/*
Class:		Bitmap

설명:		폴더에 저장된 Bitmap파일을 프로그래밍에 적용할 수 있는 
			리소스로 전환하고 관리하는 클래스

추가기능:
*/
/************************************************************************/
#pragma once
#include "Include.h"

class Bitmap
{
public:
	Bitmap();
	Bitmap( std::wstring bitmapPath );
	~Bitmap();

	void						SafeRelease();
	ID2D1Bitmap*				GetD2D1Bitmap(){return m_D2DBitmap;}

private:
	static IWICImagingFactory*	m_WICFactory;
	ID2D1Bitmap*				m_D2DBitmap;
	IWICFormatConverter*		m_FmtConverter;
	std::wstring				m_Path;
};


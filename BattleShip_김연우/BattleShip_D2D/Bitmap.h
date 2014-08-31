
#pragma once
#include "Include.h"
class Bitmap
{
public:
	Bitmap();
	Bitmap( std::wstring bitmapPath );
	~Bitmap();

	void Release();
	ID2D1Bitmap* GetD2D1Bitmap(){return m_D2DBitmap;}

private:
	static IWICImagingFactory*	m_WICFactory;
	ID2D1Bitmap*				m_D2DBitmap;
	IWICFormatConverter*		m_FmtConverter;
	std::wstring				m_Path;
};


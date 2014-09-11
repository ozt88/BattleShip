#include "Bitmap.h"
#include "BattleShipApp.h"
#include "D2DRenderer.h"

IWICImagingFactory* Bitmap::m_WICFactory = nullptr;

Bitmap::Bitmap()
	:m_D2DBitmap( nullptr ) , m_FmtConverter( nullptr ) , m_Path()
{
}

Bitmap::Bitmap( std::wstring bitmapPath )
{
	HRESULT hr;
	if( m_WICFactory == nullptr )
	{
		hr = CoCreateInstance( CLSID_WICImagingFactory ,
							   NULL , CLSCTX_INPROC_SERVER ,
							   IID_PPV_ARGS( &m_WICFactory ) );
		if( hr == REGDB_E_CLASSNOTREG )
		{
			CoCreateInstance( CLSID_WICImagingFactory1 ,
							  NULL , CLSCTX_INPROC_SERVER ,
							  IID_PPV_ARGS( &m_WICFactory ) );
		}
	}

	m_Path = bitmapPath;
	IWICBitmapDecoder* bitmapDecoder = nullptr;
	hr = m_WICFactory->CreateDecoderFromFilename(
		bitmapPath.c_str() , nullptr , GENERIC_READ ,
		WICDecodeMetadataCacheOnDemand , &bitmapDecoder
		);

	IWICBitmapFrameDecode* bitmapFrameDecode = nullptr;
	if( SUCCEEDED( hr ) )
	{
		bitmapDecoder->GetFrame( 0 , &bitmapFrameDecode );
	}

	if( SUCCEEDED( hr ) )
	{
		hr = m_WICFactory->CreateFormatConverter( &m_FmtConverter );
	}

	if( SUCCEEDED( hr ) )
	{
		hr = m_FmtConverter->Initialize(
			bitmapFrameDecode , GUID_WICPixelFormat32bppPBGRA ,
			WICBitmapDitherTypeNone , NULL ,
			0.f , WICBitmapPaletteTypeCustom
			);
	}

	D2DRenderer* renderer = BattleShipApp::GetInstance()->GetD2DRenderer();

	if( m_FmtConverter != nullptr )
	{
		renderer->GetHwndRenderTarget()->CreateBitmapFromWicBitmap(
			m_FmtConverter , nullptr , &m_D2DBitmap );
	}

	if( bitmapDecoder != nullptr )
	{
		bitmapDecoder->Release();
	}
	if( bitmapFrameDecode != nullptr )
	{
		bitmapFrameDecode->Release();
	}

}

Bitmap::~Bitmap()
{
	Release();
	if( m_WICFactory != nullptr )
	{
		m_WICFactory->Release();
		m_WICFactory = nullptr;
	}
}

void Bitmap::Release()
{
	if( m_D2DBitmap != nullptr )
	{
		m_D2DBitmap->Release();
		m_D2DBitmap = nullptr;
	}
	if( m_FmtConverter != nullptr )
	{
		m_FmtConverter->Release();
		m_D2DBitmap = nullptr;
	}
}

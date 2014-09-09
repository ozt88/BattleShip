#include "D2DRenderer.h"
#include "BattleShipApp.h"
#include "Enum.h"

D2DRenderer::D2DRenderer()
	:m_D2DFactory( nullptr ) , m_D2DRenderTarget( nullptr )
{
}


D2DRenderer::~D2DRenderer()
{
}

bool D2DRenderer::Init()
{
	HRESULT hr;
	hr = D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED ,
							&m_D2DFactory );
	if( hr != S_OK )
	{
		return false;
	}

	HWND hWnd = BattleShipApp::GetInstance()->GetHWND();
	RECT rt;
	GetClientRect( hWnd , &rt );
	D2D1_SIZE_U size = D2D1::SizeU( rt.right - rt.left , rt.bottom - rt.top );

	hr = m_D2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties() ,
		D2D1::HwndRenderTargetProperties
		( hWnd , size , D2D1_PRESENT_OPTIONS_IMMEDIATELY ) ,
		&m_D2DRenderTarget );

	if( SUCCEEDED( hr ) )
	{
		// Create a DirectWrite factory.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED ,
			__uuidof( m_D2DWriteFactory ) ,
			reinterpret_cast< IUnknown ** >( &m_D2DWriteFactory )
			);
	}

	if( SUCCEEDED( hr ) )
	{
		// Create a DirectWrite text format object.
		hr = m_D2DWriteFactory->CreateTextFormat(
			FONT_NAME ,
			NULL ,
			DWRITE_FONT_WEIGHT_NORMAL ,
			DWRITE_FONT_STYLE_NORMAL ,
			DWRITE_FONT_STRETCH_NORMAL ,
			FONT_SIZE ,
			L"" , //locale
			&m_D2DTextFormat
			);
	}
	if( SUCCEEDED( hr ) )
	{
		// Center the text horizontally and vertically.
		m_D2DTextFormat->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_CENTER );
		m_D2DTextFormat->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_CENTER );
	}

	return true;
}

bool D2DRenderer::Release()
{
	if( m_D2DFactory != nullptr )
	{
		delete m_D2DFactory;
		m_D2DFactory = nullptr;
	}
	if( m_D2DRenderTarget != nullptr )
	{
		delete m_D2DRenderTarget;
		m_D2DRenderTarget = nullptr;
	}

	return true;
}

void D2DRenderer::Clear()
{
	m_D2DRenderTarget->Clear( D2D1::ColorF( D2D1::ColorF::White ) );
}

void D2DRenderer::Begin()
{
	m_D2DRenderTarget->BeginDraw();
}

void D2DRenderer::End()
{
	m_D2DRenderTarget->EndDraw();
}



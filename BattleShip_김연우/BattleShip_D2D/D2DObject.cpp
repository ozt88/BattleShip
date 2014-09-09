#include "D2DObject.h"
#include "BattleShipApp.h"

D2DObject::D2DObject()
	:m_Parent(nullptr) , m_Angle(0.f) , m_Height(0.f) , m_Width(0.f) , 
	m_ScaleX(1.f) , m_ScaleY(1.f), m_PosX(0.f) , m_PosY(0.f) , m_ChildList()
{
	
	m_Matrix = m_Matrix.Identity();
	m_Renderer = BattleShipApp::GetInstance()->GetD2DRenderer();
}


D2DObject::~D2DObject()
{
}


void D2DObject::Render()
{
	m_Matrix =
		D2D1::Matrix3x2F::Scale( m_ScaleX , m_ScaleY )*
		D2D1::Matrix3x2F::Rotation( m_Angle )*
		D2D1::Matrix3x2F::Translation( m_PosX , m_PosY );
	
	if( m_Parent )
	{
		m_Matrix = m_Matrix * GetParent()->GetMatrix();
	}

	for( auto child : m_ChildList )
	{
		child->Render();
	}
}

void D2DObject::Update()
{
	for( auto child : m_ChildList )
	{
		child->Update();
	}
}

void D2DObject::Clear()
{
	for( auto child : m_ChildList )
	{
		child->Clear();
	}
}

void D2DObject::SetObject( float posX , float posY , float width , float height )
{
	PosX( posX ) , PosY( posY ) , Width( width ) , Height( height );
}

void D2DObject::SetParent( D2DObject* parent )
{
	if( parent == nullptr )
	{
		return;
	}
	m_Parent = parent;
}

void D2DObject::AddChild( D2DObject* child )
{
	if( child == nullptr )
	{
		return;
	}
	child->SetParent( this );
	m_ChildList.push_back( child );
}

void D2DObject::RemoveChild( D2DObject* child , bool isDelete )
{
	if( child == nullptr )
	{
		return;
	}
	m_ChildList.remove( child );

	if( isDelete )
	{
		child->Clear();
	}
}


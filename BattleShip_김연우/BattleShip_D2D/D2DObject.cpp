#include "D2DObject.h"


D2DObject::D2DObject()
	:m_Parent(nullptr) , m_Angle(0.f) , m_Height(0.f) , m_Width(0.f) , 
	m_PosX(0.f) , m_PosY(0.f) , m_ChildList()
{
	m_Matrix.Identity();
}


D2DObject::~D2DObject()
{
}


void D2DObject::Render()
{
	m_Matrix.Translation( m_PosX , m_PosY );
	m_Matrix.Rotation( m_Angle );
	m_Matrix.Scale( 1 , 1 );
	m_Matrix.Translation(1, 1);
	
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

